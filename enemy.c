#include <stdlib.h>
#include "enemy.h"
#include "grid.h"
char* enemy_types[5] = {"bat","wolf","guard","wizard","monster"};
char enemy_atk[5] = {20,30,30,60,60};
char enemy_def[5] = {10,30,60,30,60};
struct enemy* makeEnemy(struct Grid* grid){
    struct enemy* en = malloc(sizeof(struct enemy));
    en->coords = en->ag.obj.coords;
    en->hp = 100;
    en->statsindex = rand()%5;
    en->target = NULL;
bac:
    en->coords[0] = rand()%(grid->r);
    en->coords[1] = rand()%(grid->c);
    en->coords = en->ag.obj.coords;
    if(!gridrc(grid,en->coords[1],en->coords[0]))
        goto bac;
    return en;
}
void moveEnemy(struct enemy* enemy, struct Grid* grid, struct player** playarray){
    if(enemy->target) goto targeted;
    int index_of_least_score = 0;
    int least_score = 10000;
    for(int i = 0;playarray[i];i++){
       int score = abs(playarray[i]->coords[0]-enemy->coords[0])+abs(playarray[i]->coords[1]-enemy->coords[1]);
       if(score<least_score)
           least_score = score,index_of_least_score = i;
    }
    enemy->target = playarray[index_of_least_score];
    enemy->retarg = 10+(rand()%10);
targeted:
    if(!enemy->retarg--)
        enemy->target = NULL;
}
