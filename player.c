#include <stdlib.h>
#include "player.h"
#include "grid.h"
#include "enemy.h"
char* mods[10] = {"Cataclysmic","Flamboyant","Inverted","Prismatic","Congealing","Moist","Perniscious","Turbulent","Porcupinal","Flabbergasted"};
char* types[6] = {"hat","shirt","shoes","pants","weapon","ring"};
char* namearrs[6][10] = {{"Gold Circlet","Fedora","Leather Helmet","Bronze Helmet","Mail Cap","Iron Helmet","Steel Helmet","Winged Helmet","Horned Helmet","Adamantine Helmet"},{"Mage Cloak","Toga","Leather Breastplate","Bronze Breastplate","Mail Breastplate","Iron Breastplate","Steel Breastplate","Light Breastplate","Berserker Pelt-Armor","Adamantine Breastplate"},{"Mage Skirt","Cloth Pants","Leather Pants","Female Pants","Male Pants","Iron Greaves","Steel Greaves","Light Greaves","Berserker Pelt Greaves","Adamantine Greaves"},{"Mage's Feet","Crocs","Leather Boots","Bronze Boots","Mail Boots","Iron Boots","Steel Boots","Winged Boots","Berserker Boots","Adamantine Boots"},{"Mage Staff","Stick","Dagger","Bronze Scimitar","Morningstar","Stick with a brick tied on the end","Brick","Winged Rapier","Berserker Axe","Adamantine Shield"},{"Ring of Tyromancy","Unadorned Ring","Spiked Ring","Ring of Poison","Ring of Communication","Ring of Health","Ring of Defence","Ring of Speed","Ring of Fury","Ring of Marriage"}};
char defarrs[6][10] = {{0,1,3,6,7,8,9,6,4,16},{1 ,1,5,8,7,9,11,5,6,20},{3,1,3,6,7,8,10,5,4,18},{1,1,2,2,3,4,5,2,2,8},{10,1,-1,1,0 ,4 ,6 ,0 ,2 ,30},{0,0,0,0,0,0,0,0,0,0}};
char atkarrs[6][10] = {{8,0,0,1,1,1,1,2,4,-8},{12,0,0,1,1,2,3 ,3,6,-10},{7,0,0,1,0,1,1 ,3,5,-9},{4,0,0,1,1,1,1,2,3,-4},{5 ,1,5 ,8,13,10,12,15,13,-16},{0,0,0,0,0,0,0,0,0,0}};
struct player* makePlayer(struct Grid* grid){
    struct player* pl = calloc(1,sizeof(struct player));
    pl->hp = 100;
bac:
    pl->coords = pl->ag.obj.coords;
    pl->coords[0] = rand()%grid->r;
    pl->coords[1] = rand()%grid->c;
    //check in some capacity that the player isn't on top of another player... or don't, the probability is really low anyway
    if(!*gridrc(grid,pl->coords[1],pl->coords[0]))
        goto bac;
    //pl->username assigned by something
    return pl;
}
int eq(char aord,struct equipment* eq){
    return aord=='a'?atkarrs[eq->typeindex][eq->statsindex]:defarrs[eq->typeindex][eq->statsindex];
}
void attack(struct player* player,struct player* target){
    int atk = eq('a',player->hat)+ eq('a',player->shirt)+ eq('a',player->pants)+ eq('a',player->shoes)+  eq('a',player->weapon);
    int def = eq('d',target->hat)+ eq('d',target->shirt)+ eq('d',target->pants)+ eq('d',target->shoes)+  eq('d',target->weapon);
    target->hp -= atk/def * 10;
}
void attackE(struct player* player,struct enemy* target){
    int atk = eq('a',player->hat)+ eq('a',player->shirt)+ eq('a',player->pants)+ eq('a',player->shoes)+  eq('a',player->weapon);
    int def = enemy_def[target->statsindex];
    target->hp -= atk/def * 10;
}
void Eattack(struct enemy* aggressor,struct player* target){
    int atk = enemy_atk[aggressor->statsindex];
    int def = eq('d',target->hat)+ eq('d',target->shirt)+ eq('d',target->pants)+ eq('d',target->shoes)+  eq('d',target->weapon);
    target->hp -= atk/def * 10;
}
