#include <stdlib.h>
#include "player.h"
#include "enemy.h"

int heuristic(struct object* seeker,struct object* target){
    return abs(seeker->coords[0]-target->coords[0])+abs(seeker->coords[1]-target->coords[1]);
}
int astar1(struct object* seeker,struct object* target){
 
}
