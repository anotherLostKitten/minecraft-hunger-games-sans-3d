#ifndef SHMUTILS
#define SHMUTILS
char* makeshm(char* name,int* semdescriptor,int* shmdescriptor);
int accshm(int semdescriptor,int shmdescriptor,char semnum,void* dtat);
void closeshm(char* name,int semdescriptor,int shmdescriptor);
#endif
