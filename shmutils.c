#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };
char* makeshm(char* name,int* semdescriptor,int* shmdescriptor){
    int temp = open(name,O_CREAT|O_TRUNC|0644);
    close(temp);
    key_t key = ftok(name,0);
    *semdescriptor = semget(key,1,IPC_CREAT|0644);
    union semun s;
    s.val = 1;
    *shmdescriptor = shmget(key,1024,IPC_CREAT|0644);
    semctl(*semdescriptor,0,SETVAL,&s);
}

int accshm(int semdescriptor,int shmdescriptor,char semnum,void* dtat){
    struct sembuf b;
    b.sem_op = 0;
    b.sem_num = semnum;
    b.sem_flg = 0;
    /* semop */
    semop(semdescriptor,&b,1);
    if(semnum<0) dtat = shmat(shmdescriptor,NULL,0);
    else if(semnum>0) shmdt(dtat);
}

void closeshm(char* name,int semdescriptor,int shmdescriptor){
    semctl(semdescriptor,0,IPC_RMID);
    shmctl(shmdescriptor,IPC_RMID,NULL);
    remove(name);
}
