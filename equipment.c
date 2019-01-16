#include <stdlib.h>
#include "player.h"

#define NMODS 10

void prandtype(struct equipment* eq){
    eq->modindex = mods[rand()%10];
    char type = rand()%6;
    eq->typeindex = type;
    int itemindex = rand()%NMODS;
    eq->statsindex = itemindex;
}
struct equipment* random_item(){
    struct equipment* eq = malloc(sizeof(struct equipment));
    eq->coords = eq->obj.coords;
    prandtype(eq);
    return eq;
}
