#include "player.h"
#include "keysdown.h"
#include "grid.h"
#include "enemy.h"
#include "atk.h"
int process_keypress(struct keysdown* keys,int playernum,struct Grid* grid,struct player* playarray,struct enemy* enemyarray,struct equipment* equarray){
    struct player player=playarray[playernum];
    int xdir=0,ydir=0;
    if(keys->upw) xdir=0,ydir=-1;
    if(keys->downs) xdir=0,ydir=1;
    if(keys->lefta) xdir=-1,ydir=0;
    if(keys->rightd) xdir=1,ydir=0;
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
	if(*gridrc(grid,player.coords[0]+ydir,player.coords[1]+xdir)){
			player.coords[0] += ydir;
			player.coords[1] += xdir;
	}
aftermove:
    if(keys->zj) ;
    if(keys->xk){
        for(int i = 0;i<MAXEQ;i++){
            if(equarray[i].coords[0]==player.coords[0] && equarray[i].coords[1]==player.coords[1]){
                player.equipment[equarray[i].typeindex] = i;

                return 0;
            }
        }
    }
}
