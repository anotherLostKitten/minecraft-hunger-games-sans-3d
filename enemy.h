#ifndef ENEMY
#define ENEMY
#include "grid.h"
extern char* enemy_types[5];
extern char enemy_atk[5];
extern char enemy_def[5];
struct enemy{
    char statsindex;
    int hp;
    int coords[2];
};
struct enemy* makeEnemy(struct Grid* grid);
#endif
