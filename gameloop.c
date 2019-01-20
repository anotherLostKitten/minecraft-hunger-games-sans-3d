#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/types.h>
#include "shmutils.h"
#include "fs/sockets.h"
#include "itemgen.h"
#include "player.h"
#include "enemy.h"
#include "cell_auto_mapgen.h"
#include "keysdown.h"
#include "clikey.h"
#include "pkp.h"

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };

#define BILLION 1000000000
#define MAX_PLAYERS 2
#define FPS 2

int main(){
    srand(time(NULL));
    //make grid

    int wkp=server_setup();

    struct Grid* grid = mkmap(MAPSIZE,MAPSIZE);
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
    makeshm("equarray",&equsem,&equshm,sizeof(struct equipment)*MAXEQ);
    //populate and attatch to pointer shared equipment memory
    struct equipment* equarray;
    accshm(equsem,equshm,-1,&equarray);
    itemgen(grid,MAXEQ,equarray);
    accshm(equsem,equshm,1,&equarray);

    int waitshm,waitsem,*junk;
    makeshm("wait",&waitsem,&waitshm,1);
    accshm(waitsem,waitshm,-1,&junk);
    //initialize all the subservers
    for(int num_players=0;num_players<MAX_PLAYERS;num_players++){
        if(num_players==MAX_PLAYERS-1||fork()){
            int client_pipe = server_connect(wkp);
            accshm(waitsem,waitshm,1,junk);
            if(semctl(waitsem,0,GETVAL)==MAX_PLAYERS)
                semctl(waitsem,0,SETVAL,0);
            accshm(waitsem,waitshm,0,NULL);
            if(num_players==MAX_PLAYERS-1) closeshm("wait",waitsem,waitshm);
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            //write player number to client
            printf("%d\n",num_players);
            write(client_pipe,&num_players,sizeof(int));
            //write grid to client
            write(client_pipe,grid,sizeof(struct Grid)+MAPSIZE*MAPSIZE);
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

            struct keysdown* keystruct=malloc(sizeof(struct keysdown));

            clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
                if(keystruct->quit) goto quit;

                accshm(playsem,playshm,-1,&playarray);
                accshm(enemysem,enemyshm,-1,&enemyarray);
                accshm(equsem,equshm,-1,&equarray);
                process_keypress(keystruct,num_players,grid,playarray,enemyarray,equarray);
                accshm(equsem,equshm,1,&equarray);
                accshm(enemysem,enemyshm,1,&enemyarray);
                accshm(playsem,playshm,1,&playarray);
quit:

                //DO GARBAGE
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
                accshm(playsem,playshm,-1,&playarray);
                accshm(enemysem,enemyshm,-1,&enemyarray);
                char ded=0,eeded=0;
                if((long int)playarray==(long int)enemyarray) goto exity;
                if(playarray[num_players].hp<=0||keystruct->quit){
                    playarray[num_players].coords[0]=-1;
                    ded=1;
                }
                for(int i=0;i<MAX_PLAYERS;i++)
                    if(playarray[i].coords[0]==-1)
                        eeded++;
                //printf("%d\n",eeded);
                if(eeded==MAX_PLAYERS-1) goto exity;
                if(ded) exit(0);
                int hpmax=0,hpind=0;
                for(int i =0;i<MAX_PLAYERS;i++){
                    if(hpmax<playarray[i].hp){
                        hpind=i;
                        hpmax=playarray[i].hp;
                    }
                }
                //printf("hpind:%i pid:%i\n",hpind,num_players);
                if(num_players==hpind){
                    //enemy movement
                    for(int i=0;i<MAXENMY;i++){
                        if((enemyarray+i)->coords[0]==-1) continue;
                        enemove(grid,enemyarray+i,playarray);
                        if((enemyarray+i)->hp<=0)
                           (enemyarray+i)->coords[0]=-1;
                    }
                }
                accshm(enemysem,enemyshm,1,&enemyarray);
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

