#ifndef SHMUTILS
#define SHMUTILS
void makeshm(char* name,int* semdescriptor,int* shmdescriptor,int memsize);
void accshm(int semdescriptor,int shmdescriptor,char semnum,void* dtat);
void closeshm(char* name,int semdescriptor,int shmdescriptor);
#endif
