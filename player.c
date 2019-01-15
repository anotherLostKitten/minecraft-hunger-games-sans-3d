#include <stdlib.h>
#include "player.h"
#include "grid.h"
struct player* makePlayer(struct Grid* grid){
    struct player* pl = calloc(1,sizeof(struct player));
    pl->hp = 100;
bac:
    pl->coords[0] = rand()%grid->r;
    pl->coords[1] = rand()%grid->c;
    //check in some capacity that the player isn't on top of another player... or don't, the probability is really low anyway
    if(!gridrc(grid,pl->coords[1],pl->coords[0]))
        goto bac;
    //pl->username assigned by something
    return pl;
}
int eq(char aord,struct equipment* eq){
    return aord=='a'?eq->attack:eq->defense;
}
void attack(struct player* player,struct player* target){
    int atk = eq('a',player->hat)+ eq('a',player->shirt)+ eq('a',player->pants)+ eq('a',player->shoes)+  eq('a',player->weapon);
    int def = eq('d',player->hat)+ eq('d',player->shirt)+ eq('d',player->pants)+ eq('d',player->shoes)+  eq('d',player->weapon);
    target->hp = atk/def * atk;
}
