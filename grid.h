#ifndef GRID
#define GRID

struct Grid{
	char*elem;
	int r,c;
};

struct Grid*mkgrid(int r,int c);
char*gridrc(struct Grid*grid,int r,int c);
void rmgrid(struct Grid*grid);

#endif
