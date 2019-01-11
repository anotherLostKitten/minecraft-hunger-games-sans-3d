#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "fs/socket.h"
#include <time.h>
#include "updategamestate.h"
#include "subserver.h"
#define FPS 2
#define BILLION 1000000000
#define MAX_PLAYERS 6
		   
int setup(){
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
    if(!bind(sd,results->ai_addr,results->ai_addrlen))
		exit(1);
    if(!listen(sd,10))
		exit(1);
    free(hints);
    freeaddrinfo(results);
  
    for(int num_players=0;num_players<MAX_PLAYERS;num_players++){
		if(fork(sd)){
			forkproc(sd);
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

