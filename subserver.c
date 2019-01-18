#include <fcntl.c>
#include <unistd.h>
#include "fs/sockets.h"
#include "grid.h"

#define NUM_PLAYERS 4
#define FPS 2

int fork_proc(int sd,int start,int end,struct Grid* grid,char pnum){
    int to_client, from_client;
    to_client=sd;
    from_client = server_connect(&to_client);
    //make grid
    struct Grid* grid = mkmap(128,128);//this is before deletion
    //write grid to client
    write(to_client,grid,sizeof(struct Grid)+grid->r*grid->c);
    //write player number to client
    write(to_client,&pnum,4);

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
