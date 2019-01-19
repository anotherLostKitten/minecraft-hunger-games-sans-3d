#ifndef PLAYER
#define PLAYER

#include "grid.h"

#define MAPSIZE 255
#define NUM_PLAYERS 4
#define MAXEQ 50
#define MAXENMY 50

extern char* mods[10];
extern char* types[6];
extern char* namearrs[6][10];
extern char defarrs[6][10];
extern char atkarrs[6][10];
struct object{
    int coords[2];
};
struct equipment{
    struct object obj;
    /* int defense; */
    /* int attack; */
    /* char* name; */
    char statsindex;
    char typeindex;
    char modindex;
    int coords[2];
};
struct player{
    struct object obj;
    int hp;
    int gold;
    struct equipment* hat;
    struct equipment* shirt;
    struct equipment* pants;
    struct equipment* shoes;
    struct equipment* weapon;
    struct equipment* ring;
    int coords[2];
};
void makePlayer(struct Grid* grid,struct player* ptr);

#endif
