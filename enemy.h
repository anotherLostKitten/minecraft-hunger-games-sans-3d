#ifndef ENEMY
#define ENEMY
#include "grid.h"
#include "player.h"
extern char* enemy_types[5];
extern char enemy_atk[5];
extern char enemy_def[5];
struct enemy{
    struct agent ag;
    char statsindex;
    int hp;
    struct player* target;
    int retarg;
    int* coords;
};
struct enemy* makeEnemy(struct Grid* grid);
#endif
