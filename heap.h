#ifndef HEAP
#define HEAP

struct Heap{
	int*elem,size,capacity;
};

struct Heap*mkheap();

void heappush(struct Heap*heap,int e);

int heappop(struct Heap*heap);

void rmheap(struct Heap*heap);

#endif
