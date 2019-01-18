#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>
#include <sys/shm.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "shmutils.h"
#include "time.h"
#include "player.h"
#include "enemy.h"
#include "grid.h"
#include "cell_auto_mapgen.h"
#include "keysdown.h"
#include "clikey.h"

int setupSDL();
int render(struct player*player,struct Grid*grid,struct player*playarray,struct enemy*enemyarray,struct equipment*equarray);

#endif
