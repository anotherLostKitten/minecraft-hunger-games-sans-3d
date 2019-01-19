#ifndef PKP
#define PKP
#include "keysdown.h"
#include "player.h"
#include "grid.h"
#include "enemy.h"
int process_keypress(struct keysdown* keys,int player,struct Grid* grid,struct player* playarray,struct enemy* enemyarray,struct equipment* equarray);
#endif
