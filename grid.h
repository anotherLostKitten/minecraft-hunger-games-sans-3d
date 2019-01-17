#ifndef GRID
#define GRID

struct Grid{
	int r,c;
	char elem[];
};

struct Grid*mkgrid(int r,int c);
char*gridrc(struct Grid*grid,int r,int c);
void rmgrid(struct Grid*grid);
void gridprint(struct Grid*grid);
struct Grid*mkgrid2(int r,int c);
#endif
