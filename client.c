#include <fcntl.c>
#include <unistd.h>
#include "render.h"
#include "player.h"
#include "fs/sockets.h"

#define NUM_PLAYERS 4

int client(int argc, char **argv){
    int from_server, to_server;
    if (argc == 2)
	server_socket = client_setup( argv[1]);
    else
	server_socket = client_setup( TEST_IP );
    setupSDL();
    struct keysdown* keys = calloc(sizeof(struct keysdown),1);//NOTE CLIENT SIDE IN FINAL VERSION then it should be written to a pipe, the server should read the struct and execute as of now unimplemented actions based on this.
    while(!quit){    
	keys->xk=0;
	keys->zj=0;
	keys->cl=0;
        while(SDL_PollEvent(&event)){
            int crementer = 0;
            keys->xk=0;
            keys->zj=0;
            keys->cl=0;
            switch(event.type){
	    case SDL_KEYUP:
	    case SDL_KEYDOWN:
		handlekey(event,keys);
		break;
	    case SDL_QUIT:
		quit = 1;
		break;
            }
        }
	// send key struct
	// get data from server
        render(player,grid,playarray,enemyarray,eqarray);
    }
    
    return 0;
}
