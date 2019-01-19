#include "player.h"
#include "keysdown.h"
#include "grid.h"
#include "enemy.h"
#include "atk.h"
int process_keypress(struct keysdown* keys,int playernum,struct Grid* grid,struct player* playarray,struct enemy* enemyarray,struct equipment* equarray){
    struct player player=playarray[playernum];
    int xdir,ydir;
    if(keys->upw) xdir=0,ydir=1;
    if(keys->downs) xdir=0,ydir=-1;
    if(keys->lefta) xdir=-1,ydir=0;
    if(keys->rightd) xdir=1,ydir=0;
    for(int i = 0;i<NUM_PLAYERS;i++){
        if(i!=playernum && playarray[i].coords[0]==player.coords[0] + xdir && playarray[i].coords[1]==player.coords[1] + ydir){
            attack(player,playarray[i]);
            goto aftermove;
        }
    }
    for(int i = 0;i<MAXENMY;i++){
        if(enemyarray[i].coords[0]==player.coords[0] + xdir && enemyarray[i].coords[1]==player.coords[1] + ydir){
            attackE(player,enemyarray[i]);
            goto aftermove;
        }
    }
    player.coords[0] += xdir;
    player.coords[1] += ydir;
aftermove:
    if(keys->zj) ;
    if(keys->xk){
        for(int i = 0;i<MAXEQ;i++){
            if(equarray[i].coords[0]==player.coords[0] + xdir && equarray[i].coords[1]==player.coords[1] + ydir){
                player.equipment[equarray[i].typeindex] = i;

                goto aftermove;
            }
        }
    }
}
