#include <stdlib.h>
#include <stdio.h>
#include "enemy.h"
#include "grid.h"
#include "itemgen.h"
#include "atk.h"

char* enemy_types[5] = {"bat","wolf","guard","wizard","monster"};
char enemy_atk[5] = {20,30,30,60,60};
char enemy_def[5] = {10,30,60,30,60};
void makeEnemy(struct Grid* grid,struct enemy* en){
    en->hp = 100;
    en->statsindex = rand()%5;
    en->target = NULL;
bac:
    en->coords[0] = rand()%(grid->r);
    en->coords[1] = rand()%(grid->c);
    if(!*gridrc(grid,en->coords[0],en->coords[1]))
        goto bac;
}
void enemove(struct Grid* grid,struct enemy* en,struct player* playarray){
    int x = en->coords[0],y = en->coords[1];
    randir(grid,en->coords,en->coords+1);
	//printf("[%i,%i]->[%i,%i]\n",x,y,en->coords[0],en->coords[1]);
    for(int i = 0;i<NUM_PLAYERS;i++){
        if(playarray[i].coords[0]==en->coords[0] && playarray[i].coords[1]==en->coords[1]){
            //puts("attacking");
            Eattack(en,playarray+i);
            goto aftermove;
        }
    }
    return;
aftermove:
   en->coords[0]=x,en->coords[1]=y;
}
