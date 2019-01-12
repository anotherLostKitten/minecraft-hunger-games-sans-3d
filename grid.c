#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

struct Grid*mkgrid(int r,int c){
	struct Grid*a=malloc(sizeof(struct Grid));
	a->r=r;
	a->c=c;
	a->elem=calloc(r,c);
	return a;
}

char*gridrc(struct Grid*grid,int r,int c){
	return 0>r||r>=grid->r||0>c||c>=grid->c?NULL:grid->elem+r+c*grid->r;
}

void rmgrid(struct Grid*grid){
	free(grid->elem);
	free(grid);
}

void gridprint(struct Grid*grid){
    for(int y=0;y<grid->r;y++){
        for(int x=0;x<grid->c;x++)
            switch(*gridrc(grid,y,x)){
			case 1:printf("[]");break;
			case-1:printf("[]");break;
			case 0:printf("  ");break;
			default:printf("??");break;
            }
        putchar('\n');
    }
}
