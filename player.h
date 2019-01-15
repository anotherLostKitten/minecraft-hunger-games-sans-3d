#ifndef PLAYER
#define PLAYER
#include "grid.h"
extern char* mods[10];
extern char* types[6];
extern char* namearrs[6][10];
extern char defarrs[6][10];
extern char atkarrs[6][10];
struct equipment{
    /* int defense; */
    /* int attack; */
    /* char* name; */
    char statsindex;
    char typeindex;
    char modindex;
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
