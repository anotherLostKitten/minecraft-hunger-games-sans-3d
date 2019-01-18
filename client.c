#include <fcntl.c>
#include <unistd.h>
#include "render.h"
#include "player.h"
#include "fs/sockets.h"
#include "enemy.h"
#include "clickey.h"

int main(int argc, char **argv){
    int server_socket;
    if (argc == 2)
		server_socket = client_setup( argv[1]);
    else
		server_socket = client_setup( TEST_IP );
    setupSDL();

	char pid;
	struct Grid*grid=calloc(sizeof(struct Grid)+MAPSIZE*MAPSIZE,1);
	struct player*playarray=calloc(sizeof(struct player),NUM_PLAYERS);
	struct enemy*enemyarray=calloc(sizeof(struct enemy),MAXENMY);
	struct equipment*eqarray=calloc(sizeof(struct equipment),MAXEQ);
	
	read(server_socket,map,sizeof(struct Grid)+MAPSIZE*MAPSIZE);
	read(server_socker,&pid,1);
	
    struct keysdown* keys = calloc(sizeof(struct keysdown),1);
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
		write(server_socket,keys,sizeof(struct keydown));
		read(server_socket,playarray,sizeof(struct player)*NUM_PLAYERS);
		read(server_socket,enemyarray,sizeof(struct enemy)*MAXENMY);
		read(server_socket,eqarray,sizeof(struct equipment)*MAXEQ);
		render(playarray[pid],grid,playarray,enemyarray,eqarray);
    }
    
    return 0;
}
