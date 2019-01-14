#include "player.h"
#include "grid.h"
int makePlayer(struct Grid* grid){
    struct player pl = calloc(sizeof(player));
    pl->hp = 100;
bac:
    pl->coords = (int []) {rand()%grid->c,rand()%grid->r};
    if(!gridrc(grid,pl->coords[1],pl->coords[0]))
        goto bac;
    pl->defense = 30;
    pl->attack = 5;
    //pl->username assigned by something
    return 0;
}
void attack(struct player* player,struct player* target){
    int atk = player->attack;
    int def = target->defense;
    target->hp = atk/def * atk;
}
