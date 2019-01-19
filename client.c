#include <fcntl.h>
#include <unistd.h>
#include "render.h"
#include "player.h"
#include "fs/sockets.h"
#include "enemy.h"
#include "clikey.h"
#include "keysdown.h"

int main(int argc, char **argv){
    int server_socket;
    if (argc == 2)
		server_socket = client_setup( argv[1]);
    else
		server_socket = client_setup( TEST_IP );

    char quit=0;
    int pid;
    struct Grid*grid=calloc(sizeof(struct Grid)+MAPSIZE*MAPSIZE,1);
    struct player*playarray=calloc(sizeof(struct player),NUM_PLAYERS);
    struct enemy*enemyarray=calloc(sizeof(struct enemy),MAXENMY);
    struct equipment*eqarray=calloc(sizeof(struct equipment),MAXEQ);
	
    read(server_socket,&pid,sizeof(int));
    read(server_socket,grid,sizeof(struct Grid)+MAPSIZE*MAPSIZE+1);
    //gridprint(grid);
    printf("%d\n",pid);
    
    struct keysdown*keys=calloc(sizeof(struct keysdown),1);
    setupSDL();
    SDL_Event event;
	
    read(server_socket,playarray,sizeof(struct player)*NUM_PLAYERS);
    read(server_socket,enemyarray,sizeof(struct enemy)*MAXENMY);
    read(server_socket,eqarray,sizeof(struct equipment)*MAXEQ);

    while(!quit){
        keys->xk=0;
        keys->zj=0;
        keys->cl=0;
        while(SDL_PollEvent(&event)){
            int crementer = 0;
            handlekey(event,keys);
        }
		write(server_socket,keys,sizeof(struct keysdown));
        if(keys->quit) quit=1;
		read(server_socket,playarray,sizeof(struct player)*NUM_PLAYERS);
		read(server_socket,enemyarray,sizeof(struct enemy)*MAXENMY);
		read(server_socket,eqarray,sizeof(struct equipment)*MAXEQ);
		if(playarray[pid].hp==0)
			break;
		for(int i=0;i<NUM_PLAYERS;i++)
			if(i!=pid&&playarray[i].hp>0)
				goto q;
		break;
    q: 	render(pid,grid,playarray,enemyarray,eqarray);
    }
    
    return 0;
}
