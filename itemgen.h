#ifndef ITEMGEN
#define ITEMGEN

struct Grid*highs(struct Grid*map,int*n);
void itemgen(struct Grid*map,int m,struct equipment*e);
void randir(struct Grid*map,int*r,int*c);
struct equipment randeq(int r,int c);

#endif
