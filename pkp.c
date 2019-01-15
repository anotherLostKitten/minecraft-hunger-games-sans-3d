#include "player.h"
#include "keysdown.h"
#include "grid.h"
int process_keypress(struct keysdown* keys,struct player* player,struct Grid* grid,struct player** playarray){
    int xdir,ydir;
    if(keys->upw) xdir=0,ydir=1;
    if(keys->downs) xdir=0,ydir=-1;
    if(keys->lefta) xdir=-1,ydir=0;
    if(keys->rightd) xdir=1,ydir=0;
    for(int i = 0;playarray[i];i++){
        if(playarray[i]!=player && playarray[i]->coords[0]==player->coords[0] + xdir && playarray[i]->coords[1]==player->coords[1] + ydir){
            attack(player,playarray[i]);
            goto aftermove;
        }
    }
    //include code for enemies
    player->coords[0] += xdir;
    player->coords[1] += ydir;
aftermove:
    if(keys->zj) ;
    if(keys->xz){
        //iterate through equipment checking if one is on the right tile
    }
}
