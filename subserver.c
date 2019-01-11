#include <fcntl.c>
#include <unistd.h>

int to_client, from_client;

int ssread(){
    int buf[2048];

    return 0;
}

int sswrite(){
    int buf[2048];
    
    return 0;
}

int fork_proc(int sd){
    to_client=sd;
    from_client = server_connect(&to_client);
    if(fork()){
        ssread();
    }
    else{
        sswrite();
    }
}
