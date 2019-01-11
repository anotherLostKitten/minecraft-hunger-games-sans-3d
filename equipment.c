#include <stdlib.h>
#include "player.h"
#define NMODS 10
void prandtype(struct equipment* eq){
    char* mods[10] = {"Strong","Big","Huge","Shiny","Heavy","Light","Dull","Tiny","Small","Weak"};
    eq->modifier = mods[rand()%10];
    char* types[6] = {"hat","shirt","shoes","pants","weapon","ring"};
    char type = rand()%6;
    eq->type = types[type];
    char** names;
    char* attack;
    char* defense;
    switch(type){
        case 0:
            names = (char*[]){"Gold Circlet","Cloth Cap","Leather Helmet","Bronze Helmet","Mail Cap","Iron Helmet","Steel Helmet","Winged Helmet","Horned Helmet","Adamantine Helmet"};
            defense = (char[]){0,1,3,6,7,8,9,6,4,16};
            attack  = (char[]){8,0,0,1,1,1,1,2,4,-8};
            break;
        case 1:
            names = (char*[]){"Mage Cloak","Cloth Shirt","Leather Breastplate","Bronze Breastplate","Mail Breastplate","Iron Breastplate","Steel Breastplate","Light Breastplate","Berserker Pelt-Armor","Adamantine Breastplate"};
            defense = (char[]){1 ,1,5,8,7,9,11,5,6,20};
            attack  = (char[]){12,0,0,1,1,2,3 ,3,6,-10};
            break;
        case 2:
            names = (char*[]){"Mage Skirt","Cloth Pants","Leather Greaves","Bronze Greaves","Mail Pants","Iron Greaves","Steel Greaves","Light Greaves","Berserker Pelt Greaves","Adamantine Greaves"};
            defense = (char []){3,1,3,6,7,8,10,5,4,18};
            attack  = (char []){7,0,0,1,0,1,1 ,3,5,-9};
            break;
        case 3:
            names = (char* []){"Mage Shoes","Sandals","Leather Boots","Bronze Boots","Mail Boots","Iron Boots","Steel Boots","Winged Boots","Berserker Boots","Adamantine Boots"};
            defense = (char []){1,1,2,2,3,4,5,2,2,8};
            attack  = (char []){4,0,0,1,1,1,1,2,3,-4};
            break;
        case 4:
            names = (char* []){"Mage Staff","Stick","Dagger","Bronze Scimitar","Mace and Chain","Iron Longsword","Steel Claymore","Winged Rapier","Berserker Axe","Adamantine Shield"};
            defense = (char []){10,1,-1,1,0 ,4 ,6 ,0 ,2 ,30};
            attack  = (char []){5 ,1,5 ,8,13,10,12,15,13,-16};
            break;
        case 5:
            names = (char* []){"Ring of Magic","Unadorned Ring","Spiked Ring","Ring of Poison","Mail Gloves","Ring of Health","Ring of Defence","Ring of Speed","Ring of Fury","Adamantine Gauntlet"};
            defense = (char []){0,0,0,0,0,0,0,0,0,0};
            attack  = (char []){0,0,0,0,0,0,0,0,0,0};
            break;
    }
    int itemind = rand()%NMODS;
    eq->name = names[itemind];
    eq->attack = attack[itemind];
    eq->defense = defense[itemind];
}
struct equipment* random_item(){
    struct equipment* eq = malloc(sizeof(struct equipment));
    prandtype(eq);
    return eq;
}
int main(){
    free(random_item());
}
