#ifndef DUNGGEN
#define DUNGGEN

struct Grid*dunggen(int r,int c);
char clear(struct Grid*map,int r,int c,int rd,int cd);
void fill(struct Grid*map,int r,int c,int rd,int cd,int fval);
void rndpath(struct Grid*map,struct Grid*path,int*n,int r,int c);
void nxtpath(struct Grid*map,struct Grid*path,int*n,int r,int c);
void rompath(struct Grid*map,struct Grid*path,int*n,int r,int c);
void cctpath(struct Grid*map,struct Grid*path,int*n,int r,int c);
void deadend(struct Grid*map,int r,int c);

#endif
