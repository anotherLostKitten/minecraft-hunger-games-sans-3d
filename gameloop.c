#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "fs/pipe_networking.h"
#include "updategamestate.h"
#define FPS 2
#define BILLION 1000000000
int to_client;
int from_client;
int num_players = 0;
int setup(){
    signal(SIGINT,sighandler);
    mkfifo(WKP,0644);
    num_players++;
    return 0;
}
int main(){
    setup();
shandhake:
    from_client = server_handshake( &to_client );
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
