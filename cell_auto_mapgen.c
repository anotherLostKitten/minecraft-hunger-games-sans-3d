#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

#define PROB 45
#define GENERATIONS 12

int ayn_rand(){
    return (rand()%100<PROB);
}

int mapgen(struct Grid*map,struct Grid*map2){
    int x, y;
	for(y=1;y<map->r;y++)
        for(x=1;x<map->c;x++)
            *gridrc(map,y,x) = ayn_rand();
    for(y=0;y<map->r;y++)
        for(x=0;x<map->c;x++)
            *gridrc(map2,y,x) = 1;
    for(y=0;y<map->r;y++)
        *gridrc(map,y,0) = *gridrc(map,y,map->c-1) = 1;
    for(x=0;x<map->c;x++)
        *gridrc(map,map->r-1,x) = *gridrc(map,0,x) = 1;
    return 0;
}

void generation(struct Grid*map,struct Grid*map2){
    int x,y,i,j;
    for(y=1;y<map->r-1;y++)
        for(x=1;x<map->c-1;x++){
            int adjacent1 = 0, adjacent2 = 0;
            for(i=-1;i<=1;i++)
                for(j=-1;j<=1;j++)
                    if(*gridrc(map,y+i,x+j))
						adjacent1++;
            for(i=y-2;i<=y+2;i++)
                for(j=x-2;j<=x+2;j++)
                    if(abs(i-y)+abs(j-x)<4&&gridrc(map,i,j)&&*gridrc(map,i,j))
                        adjacent2++;
			*gridrc(map2,y,x)=adjacent1>=5||adjacent2<=2?1:0;
        }
}

void flood(struct Grid*map,struct Grid*map2,int r, int c, int* filled){
    *gridrc(map2,r,c) = 1;
    *filled+=1;
	for(int i=0;i<2;i++)
		for(int j=-1;j<2;j+=2)
			if(!*gridrc(map,r+i*j,c+!i*j)&&!*gridrc(map2,r+i*j,c+!i*j))
				flood(map,map2,r+i*j,c+!i*j,filled);
}

struct Grid* mkmap(int r,int c){
	srand(time(NULL));
    int filled;
regen:
    filled = 0;
    struct Grid*map = mkgrid(r,c);
    struct Grid*map2 = mkgrid(r,c);
	mapgen(map,map2);
    for(int i = 0;i<GENERATIONS;i++){
        generation(map,map2);
		struct Grid*tmp=map;
		map=map2;
		map2=tmp;
	}
    int x,y;
    do{
        y = rand()%r;
        x = rand()%c;
    }while(*gridrc(map,y,x));
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            *gridrc(map2,i,j) = 0;
    flood(map,map2,y,x,&filled);
    //printf("%f\n",(double) filled/(mapsize*mapsize));
    if(filled<r*c*9/20) goto regen;
    rmgrid(map);
    return map2;
}

