#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "fs/pipe_networking.h"
#include "updategamestate.h"
#include "subserver.h"
#define FPS 2
#define BILLION 1000000000

int max_players;

int setup(){
    mkfifo(WKP,0644);
    for(int num_players = 0;num_players<max_players;num_players++){
        if(fork()){
            forkproc();
            return 0;
        }
    }
    return 0;
}
int main(){
    setup();
shandhake:
    //wait until frame is done
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    long int nanoseconds = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
    int sleep_for = (BILLION/FPS) - nanoseconds;
    struct timespec* sleepytime = malloc(sizeof(struct timespec));
    sleepytime->tv_nsec = sleep_for;
    sleepytime->tv_sec = 0;
    nanosleep(sleepytime,NULL);
    updategamestate();
    goto shandhake;
}
