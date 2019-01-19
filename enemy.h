#ifndef ENEMY
#define ENEMY
#include "grid.h"
#include "player.h"
extern char* enemy_types[5];
extern char enemy_atk[5];
extern char enemy_def[5];
struct enemy{
    struct object obj;
    char statsindex;
    int hp;
    struct player* target;
    int retarg;
    int coords[2];
};
void makeEnemy(struct Grid* grid,struct enemy* en);
void enemove(struct Grid* grid,struct enemy* en,struct player* playarray);
#endif
