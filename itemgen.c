#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "equipment.h"
#include "grid.h"
#include "itemgen.h"


#include "dungeongen.h"

struct grid*highs(struct Grid*map, int*n){
	struct grid*highs=mkgrid(map->r,map->c);
	for(int r=1;r<map->r-1;r++)
		for(int c=1;c<map->c-1;c++){
			int v=0;
			for(int i=0;i<2;i++)
				for(int j=-1;j<2;j+=2)
					if(*gridrc(map,r+i*j,c+!i*j))
						v++;
			if(v<2){
				*gridrc(highs,r,c)=1;
				*n+=1;
			}
		}
	return highs;
}

struct equiptment*itemgen(struct Grid*map, int m){
	int n=0,c=-1;
	struct grid*h=highs(map,&n);
	struct grid*e=calloc(m,sizeof(struct equipment));
	srand(time(NULL));
	for(int r=0;r<map->r;r++)
		for(int c=0;c<map->c;c++)
			if(*gridrc(h,r,c)&&rand()%n<m&&++c<m){
				int rt=r,ct=c;
				for(int q=0;q<3;q++)
					randir(map,&r,&c);
				e[c]=randeq(rt,ct);
			}
	rmgrid(h);
	return e;	
}

void randir(struct Grid*map,int*r,int*c){
	char d=0,n=0;
	for(char i=0;i<4;i++)
		d|=(n+=*gridrc(map,i&2?*r:*r+i-1,i&2?*c+i-2:*c)?1:0)-n<<i;
	for(char ra=rand()%n,i=0;i<4;i++)
		if(d&1<<i&&!ra--){
		    *r+=i&2?0:i-1;
			*c+=i&2?i-2:0;
			return;
		}
}

struct equipment randeq(int r,int c){
	struct object crd = {{r,c}};
	struct equipment e = {crd, rand()%10, rand()%6, rand()%10, &e.obj.coords};
	return e;
}

int main(){

}
