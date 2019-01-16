#ifndef ATK
#define ATK
#include "player.h"
#include "enemy.h"
void attack(struct player* player,struct player* target);
void attackE(struct player* player,struct enemy* target);
void Eattack(struct enemy* aggressor,struct player* target);
#endif
