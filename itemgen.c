#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "equipment.h"
#include "grid.h"
#include "itemgen.h"


#include "dungeongen.h"

int*highs(struct Grid*map, int n){
	int*t=calloc(map->r,map->c),f[n],q=0;
	for(int r=1;r<map->r-1;r++)
		for(int c=1;c<map->c-1;c++){
			int v=0;
			for(int i=0;i<2;i++)
				for(int j=-1;j<2;j+=2)
					if(*gridrc(map,r+i*j,c+!i*j))
						v++;
			if(v<2){
				if(q>map->r*map->c)
					goto q;
				f[q++]=r;
				f[q++]=c;
			}
		}
 q:

}

q main(){
	struct Grid*a=dunggen(49,101); 
	gridprint(a);
	int*b=highs(a);
	for(int i=0;b[i];i+=2)
		printf("(%i,%i)\n",b[i],b[i+1]);
	return 0;
}
