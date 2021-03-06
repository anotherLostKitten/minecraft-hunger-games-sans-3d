
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "itemgen.h"
#include "player.h"

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
    return highs;
}

void itemgen(struct Grid*map, int m, struct equipment*e){
    int n=0,cr=-1;
    struct Grid*h=highs(map,&n);
    if(n){
		srand(time(NULL));
		for(int r=0;r<map->r;r++)
			for(int c=0;c<map->c;c++)
				if(*gridrc(h,r,c)&&rand()%n<m&&++cr<m){
					int rt=r,ct=c;
					for(int q=0;q<3||!*gridrc(map,rt,ct);q++)
						randir(map,&rt,&ct);
					e[cr]=randeq(rt,ct);
					printf("item spawned at [%i,%i] -- map = %i\n",rt,ct,*gridrc(map,rt,ct)); // --------------
				}
    }
    rmgrid(h);
}

void randir(struct Grid*map,int*r,int*c){
    char d=0,n=0;
    for(char i=0;i<4;i++){
		char b=*gridrc(map,i&1?*r:*r+i-1,i&1?*c+i-2:*c)?1:0;
		n+=b;
		d|=b<<i;
    }
	for(char ra=rand()%n,i=0;i<4;i++)
		if(d&(1<<i)&&!ra--){
			*r+=i&1?0:i-1;
			*c+=i&1?i-2:0;
			return;
		}
}

struct equipment randeq(int r,int c){
    struct object crd = {{r,c}};
    struct equipment q = {crd, rand()%10, rand()%6, rand()%10, {r, c}};
    return q;
}


char item_vacant(struct equipment*eqarray,int r,int c){
    for(int i=0;i<MAXEQ&&eqarray[i].coords;i++)
		if(eqarray[i].coords[0]==r&&eqarray[i].coords[1]==c)
			return 0;
    return 1;
}

void dropitems(struct player*p,struct equipment*eqarray,struct Grid*map){
    for(int i=0;i<6;i++)
		if(p->equipment[i]+1){
			int r=p->coords[0],c=p->coords[1];
			while(1){
				if(item_vacant(eqarray,r,c)){
					eqarray[p->equipment[i]].coords[0]=r;
					eqarray[p->equipment[i]].coords[1]=c;
					break;
				}
				randir(map,&r,&c);
			}
			p->equipment[i]=-1;
		}
}

