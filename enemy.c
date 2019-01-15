#include <stdlib.h>
#include "enemy.h"
#include "grid.h"
char* enemy_types[5] = {"bat","wolf","guard","wizard","monster"};
char enemy_atk[5] = {20,30,30,60,60};
char enemy_def[5] = {10,30,60,30,60};
struct enemy* makeEnemy(struct Grid* grid){
    struct enemy* en = malloc(sizeof(struct enemy));
    en->hp = 100;
    en->statsindex = rand()%5;
bac:
    en->coords[0] = rand()%grid->r;
    en->coords[1] = rand()%grid->c;
    if(!gridrc(grid,en->coords[1],en->coords[0]))
        goto bac;
    return en;
}
