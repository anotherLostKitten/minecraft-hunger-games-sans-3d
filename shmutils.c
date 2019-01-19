#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };
void makeshm(char* name,int* semdescriptor,int* shmdescriptor,int memsize){
    int temp;
    if(!access(name,F_OK))
        temp = open(name,O_TRUNC|0644);
    else
        temp = open(name,O_CREAT|0644);
    close(temp);
    key_t key = ftok(name,0);
    *semdescriptor = semget(key,1,IPC_CREAT|0644);
    union semun sn;
    sn.val = 1;
    semctl(*semdescriptor,0,SETVAL,1);
    *shmdescriptor = shmget(key,memsize,IPC_CREAT|0644);
}

void accshm(int semdescriptor,int shmdescriptor,char semp,void** dtat){
    struct sembuf b;
    b.sem_op = semp;
    b.sem_num = 0;
    b.sem_flg = 0;
    /* semop */
    semop(semdescriptor,&b,1);
    if(semp<0) *dtat = shmat(shmdescriptor,NULL,0);
    else if(semp>0) shmdt(*dtat);
}

void closeshm(char* name,int semdescriptor,int shmdescriptor){
    semctl(semdescriptor,0,IPC_RMID);
    shmctl(shmdescriptor,IPC_RMID,NULL);
    remove(name);
}
