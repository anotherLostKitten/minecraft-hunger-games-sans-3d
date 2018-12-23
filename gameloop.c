#include "input.h"
#include "updategamestate.h"
#include "render.h" 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define FPS 2
#define BILLION 1000000000
int setup(){
    return 0;
}
int main(){
    setup();
    while(1){
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        input();
        updategamestate();
        render();
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        long int nanoseconds = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
        int sleep_for = (BILLION/FPS) - nanoseconds;
        struct timespec* sleepytime = malloc(sizeof(struct timespec));
        sleepytime->tv_nsec = sleep_for;
        sleepytime->tv_sec = 0;
        nanosleep(sleepytime,NULL);
    }
}
