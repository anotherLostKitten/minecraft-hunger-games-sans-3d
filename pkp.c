#include <stdio.h>
#include "player.h"
#include "keysdown.h"
#include "grid.h"
#include "enemy.h"
#include "atk.h"
int process_keypress(struct keysdown* keys,int playernum,struct Grid* grid,struct player* playarray,struct enemy* enemyarray,struct equipment* equarray){
    struct player player=playarray[playernum];
    int xdir=0,ydir=0;
    if(keys->upw) ydir=-1;
    if(keys->downs) ydir=1;
    if(keys->lefta) xdir=-1;
    if(keys->rightd) xdir=1;
    printf("processing keypress %d %d\n",xdir,ydir);
    for(int i = 0;i<NUM_PLAYERS;i++){
        if(i!=playernum && playarray[i].coords[0]==player.coords[0] + ydir && playarray[i].coords[1]==player.coords[1] + xdir){
            attack(player,playarray[i]);
            goto aftermove;
        }
    }
    for(int i = 0;i<MAXENMY;i++){
        if(enemyarray[i].coords[0]==player.coords[0] + ydir && enemyarray[i].coords[1]==player.coords[1] + xdir){
            attackE(player,enemyarray[i]);
            goto aftermove;
        }
    }
	if(*gridrc(grid,playarray[playernum].coords[0]+ydir,playarray[playernum].coords[1]+xdir)){
			playarray[playernum].coords[0] += ydir;
			playarray[playernum].coords[1] += xdir;
	}
aftermove:
    if(keys->zj) ;
    if(keys->xk){
        for(int i = 0;i<MAXEQ;i++){
            if(equarray[i].coords[0]==player.coords[0] && equarray[i].coords[1]==player.coords[1]){
		if(player.equipment[equarray[i].typeindex]+1){
		    equarray[player.equipment[equarray[i].typeindex]].coords[0]=player.coords[0];
		    equarray[player.equipment[equarray[i].typeindex]].coords[1]=player.coords[1];
		}
		player.equipment[equarray[i].typeindex] = i;
		equarray[i].coords[0]=-1;
		equarray[i].coords[1]=-1;
                return 0;
            }
        }
    }
}
