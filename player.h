#ifndef PLAYER
#define PLAYER
#include "grid.h"
struct equipment{
    int defense;
    int attack;
    char* name;
    char* modifier;
    char* type;//hat,shirt,pants,shoes,weapon,etc;
    int coords[2];
};
struct player{
    int hp;
    char* username;
    int gold;
    struct equipment* hat;
    struct equipment* shirt;
    struct equipment* pants;
    struct equipment* shoes;
    struct equipment* weapon;
    struct equipment* ring;
    struct equipment** inv;
    int coords[2];
};
void attack(struct player* player,struct player* target);
struct player* makePlayer(struct Grid* grid);
#endif
