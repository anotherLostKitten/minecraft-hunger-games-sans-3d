#ifndef PLAYER
#define PLAYER
struct equipment{
    int defense;
    int attack;
    char* name;
    char* modifier;
    char* type;//hat,shirt,pants,shoes,weapon,etc;
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
int makeplayer(struct Grid* grid);
#endif
