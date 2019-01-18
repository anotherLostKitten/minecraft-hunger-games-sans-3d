#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include "grid.h"
#include "shmutils.h"

struct Grid*mkgrid(int r,int c){
	struct Grid*a = calloc(sizeof(struct Grid),r*c);
	a->r=r;
	a->c=c;
	return a;
}
char*gridrc(struct Grid*grid,int r,int c){
	return 0>r||r>=grid->r||0>c||c>=grid->c?NULL:grid->elem+r+c*grid->r;
}

void rmgrid(struct Grid*grid){
	free(grid);
}

void gridprint(struct Grid*grid){
    for(int y=0;y<grid->r;y++){
        for(int x=0;x<grid->c;x++)
            switch(*gridrc(grid,y,x)){
			case 1:printf("  ");break;
			case 0:printf("[]");break;
			case 2:printf("--");break;
			default:printf("%s%i",(*gridrc(grid,y,x)<10?" ":""),*gridrc(grid,y,x));break;
            }
        putchar('\n');
    }
}
