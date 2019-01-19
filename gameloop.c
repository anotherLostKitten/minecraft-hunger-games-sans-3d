#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "shmutils.h"
#include "fs/sockets.h"
#include "itemgen.h"
#include "player.h"
#include "enemy.h"
#include "cell_auto_mapgen.h"
#include "keysdown.h"
#include "pkp.h"

#define BILLION 1000000000
#define MAX_PLAYERS 4
#define FPS 2

int main(){
    srand(time(NULL));
    //make grid

    int wkp=server_setup();

    struct Grid* grid = mkmap(130,128);
    struct timespec start, end;
    //initialize player array shared memory
    int playsem,playshm;
    makeshm("playarray",&playsem,&playshm,sizeof(struct player)*MAX_PLAYERS);
    //populate and attatch to pointer shared player memory
    struct player* playarray;
    accshm(playsem,playshm,-1,&playarray);
    for(char np=0;np<MAX_PLAYERS;np++) makePlayer(grid,playarray+np);
    accshm(playsem,playshm,1,&playarray);
    //initialize enemy shared memory
    int enemysem,enemyshm;
    makeshm("enemyarray",&enemysem,&enemyshm,sizeof(struct enemy)*MAXENMY);
    //populate and attatch to pointer shared enemy memory
    struct enemy* enemyarray;
    accshm(enemysem,enemyshm,-1,&enemyarray);
    for(char ne=0;ne<MAXENMY;ne++) makeEnemy(grid,enemyarray+ne);
    accshm(enemysem,enemyshm,1,&enemyarray);
    //initialize equipment shared memory
    int equsem,equshm;
    makeshm("equarray",&equsem,&equshm,sizeof(struct enemy)*MAXENMY);
    //populate and attatch to pointer shared equipment memory
    struct equipment* equarray;
    accshm(equsem,equshm,-1,&equarray);
    itemgen(grid,MAXEQ,equarray);
    accshm(equsem,equshm,1,&equarray);

    int waitshm,waitsem,*junk;
    makeshm("wait",&waitsem,&waitshm,1);
    accshm(waitsem,waitshm,-1,&junk);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    //initialize all the subservers
    for(char num_players=0;num_players<MAX_PLAYERS;num_players++){
        if(num_players==MAX_PLAYERS-1||fork()){
            int client_pipe = server_connect(&wkp);
            printf("%d %d\n",MAX_PLAYERS-1,num_players);
            accshm(waitsem,waitshm,num_players==MAX_PLAYERS-1?4:-1,&junk);
            if(num_players==MAX_PLAYERS) closeshm("wait",waitsem,waitshm);

            //write grid to client
            write(client_pipe,grid,sizeof(struct Grid)+grid->r*grid->c);
            //write player number to client
            write(client_pipe,&num_players,4);
            //access and write player array to the client
            struct player* player;
            accshm(playsem,playshm,-1,&playarray);
            write(client_pipe,playarray,sizeof(struct player)*MAX_PLAYERS);
            accshm(playsem,playshm,1,&playarray);
            //player = &playarray[num_players];
            //access and write enemy array to the client
            accshm(enemysem,enemyshm,-1,&enemyarray);
            write(client_pipe,enemyarray,sizeof(struct enemy)*MAXENMY);
            accshm(enemysem,enemyshm,1,&enemyarray);
            //access and write equipment array to the client
            accshm(equsem,equshm,-1,&equarray);
            write(client_pipe,equarray,sizeof(struct equipment)*MAXEQ);
            accshm(equsem,equshm,1,&equarray);

            struct keysdown* keystruct;

            while(1){
                long int nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
                int sleep_for = (1000000000/FPS) - nanoseconds;
                struct timespec* sleepytime = malloc(sizeof(struct timespec));
                sleepytime->tv_nsec = sleep_for;
                sleepytime->tv_sec = 0;
                nanosleep(sleepytime,NULL);
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);

                //recieve keysdown struct from client
                read(client_pipe,keystruct,sizeof(struct keysdown));

                accshm(playsem,playshm,-1,&playarray);
                accshm(enemysem,enemyshm,-1,&enemyarray);
                accshm(equsem,equshm,-1,&equarray);
                process_keypress(keystruct,num_players,grid,playarray,enemyarray,equarray);
                accshm(equsem,equshm,1,&equarray);
                accshm(enemysem,enemyshm,1,&enemyarray);
                accshm(playsem,playshm,1,&playarray);

                //DO GARBAGE
                accshm(playsem,playshm,-1,&playarray);
                char ded=0,eeded=0;
                if(playarray[num_players].hp<=0){
                    playarray[num_players].coords[0]=-1;
                    ded=1;
                }
                for(int i=0;i<MAX_PLAYERS;i+=1+(i==num_players))
                    if(playarray[i].hp<=0)
                        eeded++;
                if(eeded==MAX_PLAYERS-1) goto exity;
                write(client_pipe,playarray,sizeof(struct player)*MAX_PLAYERS);

                if(ded) goto exity;
                accshm(playsem,playshm,1,&playarray);
                //player = &playarray[num_players];
                //access and write enemy array to the client
                accshm(enemysem,enemyshm,-1,&enemyarray);
                write(client_pipe,enemyarray,sizeof(struct enemy)*MAXENMY);
                accshm(enemysem,enemyshm,1,&enemyarray);
                //access and write equipment array to the client
                accshm(equsem,equshm,-1,&equarray);
                write(client_pipe,equarray,sizeof(struct equipment)*MAXEQ);
                accshm(equsem,equshm,1,&equarray);
                //enemove 
                accshm(playsem,playshm,-1,&playarray);
                int hpmax=0,hpind=0;
                for(int i =0;i<MAX_PLAYERS;i++){
                    if(hpmax<playarray[i].hp){
                        hpind=i;
                        hpmax=playarray[i].hp;
                    }
                }
                if(num_players==hpind){
                    accshm(enemysem,enemyshm,-1,&enemyarray);
                    //enemy movement
                    for(int i=0;i<MAXENMY;i++){
                        enemove(grid,enemyarray[i],playarray); 
                    }
                    accshm(enemysem,enemyshm,1,&enemyarray);
                }
                accshm(playsem,playshm,1,&playarray);

                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
        }
    }
exity:
    closeshm("playarray",playsem,playshm);
    closeshm("enemyarray",enemysem,enemyshm);
    closeshm("equarray",equsem,equshm);
    rmgrid(grid);
    return 0;
}

