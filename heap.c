#include <stdlib.h>
#include "heap.h"

struct Heap*mkheap(){
	struct Heap*heap=malloc(sizeof(struct Heap));
	heap->size=0;
	heap->capacity=10;
	heap->elem=calloc(heap->capacity,sizeof(int));
	return heap;
}

void swap(int*elem,int a,int b){
	int tmp=elem[b];
	elem[b]=elem[a];
	elem[a]=tmp;
}

void heappush(struct Heap*heap,int e){
	int i=heap->size++;
	if(i==heap->capacity)
		heap->elem=realloc(heap->elem,2*i*sizeof(int));
    for(heap->elem[i]=e;i>0&&heap->elem[i]<heap->elem[(i-1)/2];i=(i-1)/2)
		swap(heap->elem,i,(i-1)/2);
}

int heappop(struct Heap*heap){
	int tmp=*heap->elem;
	*heap->elem=heap->elem[--heap->size];
	for(int i=0,nxt;heap->elem[i*2+1];i=nxt)
		swap(heap->elem,i,nxt=heap->elem[i*2+2]?(heap->elem[i*2+2]>heap->elem[i*2+1]?i*2+1:i*2+2):i*2+2);
}

void rmheap(struct Heap*heap){
	free(heap->elem);
	free(heap);
}
