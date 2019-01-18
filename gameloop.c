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

#define BILLION 1000000000
#define MAX_PLAYERS 6
#define FPS 2

int main(){
    srand(time(NULL));
    int sd=socket(AF_INET,SOCK_STREAM,0);
    if(!sd)
        exit(1);
    struct addrinfo*hints,*results;
    hints=(struct addrinfo*)calloc(1,sizeof(struct addrinfo));
    hints->ai_family=AF_INET;//IPv4 address
    hints->ai_socktype=SOCK_STREAM;//TCP socket
    hints->ai_flags=AI_PASSIVE;//Use all valid addresses
    getaddrinfo(NULL,PORT,hints,&results);//NULL = local address
    if(bind(sd,results->ai_addr,results->ai_addrlen))
        exit(1);
    if(listen(sd,10))
        exit(1);
    free(hints);
    freeaddrinfo(results);

    //make grid
    struct Grid* grid = mkmap(130,128);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    //initialize player array shared memory
    int playsem,playshm;
    makeshm("playarray",&playsem,&playshm,sizeof(struct player)*1);
    //populate and attatch to pointer shared player memory
    struct player* playarray;
    accshm(playsem,playshm,-1,&playarray);
    for(char np=0;np<MAX_PLAYERS;np++) makePlayer(grid,&(playarray[np]));
    accshm(playsem,playshm,1,&playarray);
    //initialize enemy shared memory
    int enemysem,enemyshm;
    makeshm("enemyarray",&enemysem,&enemyshm,sizeof(struct enemy)*50);
    //populate and attatch to pointer shared enemy memory
    struct enemy* enemyarray;
    accshm(enemysem,enemyshm,-1,&enemyarray);
    for(char ne=0;ne<50;ne++) makeEnemy(grid,&(enemyarray[ne]));
    accshm(enemysem,enemyshm,1,&enemyarray);
    //initialize equipment shared memory
    int equsem,equshm;
    makeshm("equarray",&equsem,&equshm,sizeof(struct enemy)*50);
    //populate and attatch to pointer shared equipment memory
    struct equipment* equarray;
    accshm(equsem,equshm,-1,&equarray);
    itemgen(grid,50,equarray);
    accshm(equsem,equshm,1,&equarray);
    //initialize all the subservers
    for(char num_players=0;num_players<MAX_PLAYERS;num_players++){
        if(num_players==MAX_PLAYERS-1||fork()){
            struct player* player= &playarray[num_players];
            int to_client, from_client;
            to_client=sd;
            from_client = server_connect(&to_client);
            //write grid to client
            write(to_client,grid,sizeof(struct Grid)+grid->r*grid->c);
            //write player number to client
            write(to_client,&num_players,4);
            //access and write player array to the client
            accshm(playsem,playshm,-1,&playarray);
            write(to_client,playarray,sizeof(player));
            accshm(playsem,playshm,1,&playarray);

            while(1/*temp*/){
                long int nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
                int sleep_for = (1000000000/FPS) - nanoseconds;
                struct timespec* sleepytime = malloc(sizeof(struct timespec));
                sleepytime->tv_nsec = sleep_for;
                sleepytime->tv_sec = 0;
                nanosleep(sleepytime,NULL);
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                //DO GARBAGE

                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
        }
    }
    closeshm("playarray",playsem,playshm);
    closeshm("enemyarray",enemysem,enemyshm);
    closeshm("equarray",equsem,equshm);
    return 0;
}

