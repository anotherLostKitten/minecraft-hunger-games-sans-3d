#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "equipment.h"
#include "grid.h"
#include "itemgen.h"


#include "dungeongen.h"

struct Grid*highs(struct Grid*map, int*n){
	struct Grid*highs=mkgrid(map->r,map->c);
	for(int r=1;r<map->r-1;r++)
		for(int c=1;c<map->c-1;c++)
			if(*gridrc(map,r,c)){
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
	gridprint(highs);
	return highs;
}

struct equipment*itemgen(struct Grid*map, int m){
	int n=0,cr=-1;
	struct Grid*h=highs(map,&n);
	if(!n){
		rmgrid(h);
		return NULL;
	}
	struct equipment*e=calloc(m,sizeof(struct equipment));
	srand(time(NULL));
	for(int r=0;r<map->r;r++)
		for(int c=0;c<map->c;c++)
			if(*gridrc(h,r,c)&&rand()%n<m&&++cr<m){
				int rt=r,ct=c;
				for(int q=0;q<3;q++)
					randir(map,&rt,&ct);
				e[cr]=randeq(rt,ct);
			}
	printf("ok\n");
	rmgrid(h);
	printf("\nitem ROYALE\n=====\ncords [%i,%i]\nstatsindex %i\ntypeindex %i\nmodindex %i\n",e->obj.coords[0],e->obj.coords[1],e->statsindex,e->typeindex,e->modindex);
	return e;	
}

void randir(struct Grid*map,int*r,int*c){
	char d=0,n=0,b;
	for(char i=0;i<4;i++){
		n+=b=gridrc(map,i&2?*r:*r+i-1,i&2?*c+i-2:*c)&&*gridrc(map,i&2?*r:*r+i-1,i&2?*c+i-2:*c)?1:0;
		d|=b<<i;
	}
	if(n)
		for(char ra=rand()%n,i=0;i<4;i++)
			if(d&1<<i&&!ra--){
				*r+=i&2?0:i-1;
				*c+=i&2?i-2:0;
				return;
			}
}

struct equipment randeq(int r,int c){
	struct object crd = {{r,c}};
	struct equipment q = {crd, rand()%10, rand()%6, rand()%10, NULL};
	return q;
}

int main(){
	struct Grid*map=dunggen(51,101);
	struct equipment*items=itemgen(map,30);
	for(int i=0;i<30;i++)
		printf("\nitem %i\n=====\ncords [%i,%i]\nstatsindex %i\ntypeindex %i\nmodindex %i\n",i,items[i].obj.coords[0],items[i].obj.coords[1],items[i].statsindex,items[i].typeindex,items[i].modindex);
	return 0;
}
