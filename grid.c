#include <stdlib.h>
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
