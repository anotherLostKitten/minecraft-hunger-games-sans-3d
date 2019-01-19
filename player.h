#ifndef PLAYER
#define PLAYER

#include "grid.h"

#define MAPSIZE 64
#define NUM_PLAYERS 2
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
    //these are ints now because they say how much space is left in the array
    int equipment[6];
    int coords[2];
};
void makePlayer(struct Grid* grid,struct player* ptr);

#endif
