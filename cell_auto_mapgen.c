#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

#define mapsize 512

struct Grid* map,* map2;
int prob = 45, generations = 12;
int ayn_rand(){
    return (rand()%100<prob);
}

int mapgen(){
    int x, y;
    map = mkgrid(mapsize,mapsize);
    map2 = mkgrid(mapsize,mapsize);
    for(y=1;y<mapsize;y++)
        for(x=1;x<mapsize;x++)
            *gridrc(map,y,x) = ayn_rand();
    for(y=0;y<mapsize;y++)
        for(x=0;x<mapsize;x++)
            *gridrc(map2,y,x) = 1;
    for(y=0;y<mapsize;y++)
        *gridrc(map,y,0) = *gridrc(map,y,mapsize-1) = 1;
    for(x=0;x<mapsize;x++)
        *gridrc(map,mapsize-1,x) = *gridrc(map,0,x) = 1;
    return 0;
}

void generation(){
    int x,y,i,j;
    for(y=1;y<mapsize-1;y++)
        for(x=1;x<mapsize-1;x++){
            int adjacent1 = 0, adjacent2 = 0;
            for(i=-1;i<=1;i++)
                for(j=-1;j<=1;j++)
                    if(*gridrc(map,y+i,x+j)) adjacent1++;
            for(i=y-2;i<=y+2;i++)
                for(j=x-2;j<=x+2;j++){
                    if(abs(i-y)==2&&abs(j-x)==2)
                        continue;
                    if(i<0||j<0||i>=mapsize||j>=mapsize)
                        continue;
                    if(*gridrc(map,i,j))
                        adjacent2++;
                }
            if(adjacent1>=5||adjacent2<=2)
                *gridrc(map2,y,x) = 1;
            else
                *gridrc(map2,y,x) = 0;
        }
    for(y=1;y<mapsize-1;y++)
        for(x=1;x<mapsize-1;x++)
            *gridrc(map,y,x) = *gridrc(map2,y,x);
}

void flood(int x, int y, int* filled){
    *gridrc(map2,y,x) = 0;
    (*filled)++;
    int row[] = {-1,0,1,0};
    int col[] = {0,-1,0,1};
    for(int i = 0;i<4;i++)
        if(!*gridrc(map,y+row[i],x+col[i])&&*gridrc(map2,y+row[i],x+col[i]))
            flood(x+col[i],y+row[i],filled);
}

Grid* mkmap(){
    int filled;
regen:
    filled = 0;
    mapgen();
    for(int i = 0;i<generations;i++)
        generation();
    int x,y;
    do{
        x = rand()%mapsize;
        y = rand()%mapsize;
    }while(*gridrc(map,y,x));
    for(int i=0;i<mapsize;i++)
        for(int j=0;j<mapsize;j++)
            *gridrc(map2,i,j) = 1;
    flood(x,y,&filled);
    //printf("%f\n",(double) filled/(mapsize*mapsize));
    if((double) filled/(mapsize*mapsize)<.45) goto regen;
    rmgrid(map);
    return map2;
}
