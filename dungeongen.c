#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "dungeongen.h"
#include "cell_auto_mapgen.h"

#define TPR 200
#define MAX_TRIES 100
#define R_SIZE_MIN 5
#define R_SIZE_DELTA 3
#define DEADEND 20

struct Grid*dunggen(int r,int c){
	srand(time(NULL));
	struct Grid*map=mkgrid(r,c),*path=mkgrid(r,c);
	for(int i=0;i<r*c/TPR;i++)
		for(int tries=0;tries<MAX_TRIES;tries++){
			int rd=rand()%R_SIZE_DELTA*2+R_SIZE_MIN,cd=rand()%R_SIZE_DELTA*2+R_SIZE_MIN,r=rand()%(map->r-rd)/2*2+1,c=rand()%(map->c-cd)/2*2+1;
			if(clear(map,r,c,rd,cd)){
				fill(map,r,c,rd,cd,-1);
				break;
			}
		}
	int n=0;
	for(int i=1;i<map->r;i+=2)
		for(int j=1;j<map->c;j+=2)
			if(!*gridrc(map,i,j)){
				nxtpath(map,path,&n,i,j);
				if(n)goto z;
			}
 z: while(n)
		rndpath(map,path,&n,r,c);
	rmgrid(path);
	for(int i=1;i<map->r;i+=2)
		for(int j=1;j<map->c;j+=2)
			if(*gridrc(map,i,j)==1&&rand()%DEADEND)
				deadend(map,i,j);
	//gridprint(map);
	return map;
}

char clear(struct Grid*map,int r,int c,int rd,int cd){
	//printf("testing [%i,%i] to [%i,%i]\n",r,c,r+rd,c+cd);
	for(int i=r;i<r+rd;i++)
		for(int j=c;j<c+cd;j++)
			if(!gridrc(map,i,j)||*gridrc(map,i,j))
				return 0;
	return 1;
}

void fill(struct Grid*map,int r,int c,int rd,int cd,int fval){
	//printf("filling [%i,%i] to [%i,%i]\n",r,c,r+rd,c+cd);
	for(int i=r;i<r+rd;i++)
		for(int j=c;j<c+cd;j++)
			*gridrc(map,i,j)=fval;
}

void rndpath(struct Grid*map,struct Grid*path,int*n,int r,int c){
    int e=rand()%*n;
	for(r=1;r<path->r;r++)
		for(c=1;c<path->c;c++)
			if(*gridrc(path,r,c)&&!e--)
				goto b;
 b:	cctpath(map,path,n,r,c);
}

void nxtpath(struct Grid*map,struct Grid*path,int*n,int r,int c){
	for(int i=0;i-2;i++)
		for(int j=-2;j<3;j+=4)
			if(gridrc(map,r+i*j,c+!i*j))
				*n+=(*gridrc(path,r+i*j/2,c+!i*j/2)=*gridrc(path,r+i*j/2,c+!i*j/2)?0:j+2*i+*gridrc(map,r+i*j,c+!i*j)+4)?1:-1;
	*gridrc(map,r,c)=1;
}

void rompath(struct Grid*map,struct Grid*path,int*n,int r,int c){
	if(*gridrc(map,r,c)+1)return;
	*gridrc(map,r,c)=2;
	for(int i=0;i-2;i++)
		for(int j=-2;j<3;j+=4){
			rompath(map,path,n,r+i*j/2,c+!i*j/2);
			if(r&1&&c&1&&gridrc(map,r+i*j,c+!i*j)&&*gridrc(map,r+i*j/2,c+!i*j/2)-2&&*gridrc(map,r+i*j/2,c+!i*j/2)+1)
				*n+=(*gridrc(path,r+i*j/2,c+!i*j/2)=*gridrc(path,r+i*j/2,c+!i*j/2)?0:j+2*i+*gridrc(map,r+i*j,c+!i*j)+4)?1:-1;
		}
}

void cctpath(struct Grid*map,struct Grid*path,int*n,int r,int c){
	//printf("path connection @ (%i,%i)[type:%i] out of -- %i\n",r,c,*gridrc(path,r,c),*n);
	switch(*gridrc(path,r,c)){
	case 1:rompath(map,path,n,r,c-1);break; //-1 = 1
	case 2:nxtpath(map,path,n,r,c-1);break; // 0 = 1
	case 3:rompath(map,path,n,r-1,c);break; //-1 | 1
	case 4:nxtpath(map,path,n,r-1,c);break; // 0 | 1
	case 5:rompath(map,path,n,r,c+1);break; // 1 =-1
	case 6:nxtpath(map,path,n,r,c+1);break; // 1 = 0
	case 7:rompath(map,path,n,r+1,c);break; // 1 |-1
	case 8:nxtpath(map,path,n,r+1,c);break; // 1 | 0
	}
	*gridrc(map,r,c)=1;
}

void deadend(struct Grid*map,int r,int c){
	//printf("(%i,%i)\n",r,c);
	int n=0,fr=0,fc=0;
	for(int i=0;i-2;i++)
		for(int j=-1;j<2;j+=2)
			if(*gridrc(map,r+i*j,c+!i*j)){
				n++;
				fr=r+i*j;
				fc=c+!i*j;
			}
	if(n<2){
		*gridrc(map,r,c)=0;
		if(n)
			deadend(map,fr,fc);
	}
}

