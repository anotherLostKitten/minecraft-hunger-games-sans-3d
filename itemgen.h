#ifndef ITEMGEN
#define ITEMGEN

struct Grid*highs(struct Grid*map,int*n);
struct equipment*itemgen(struct Grid*map,int m);
void randir(struct Grid*map,int*r,int*c);
struct equipment randeq(int r,int c);

#endif
