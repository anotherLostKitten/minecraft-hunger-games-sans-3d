#include <fcntl.c>
#include <unistd.h>
#include <signal.h>

int to_client, from_client;

int ssread(int from_client){
    int buf[2048];

    return 0;
}

int sswrite(int to_client){
    int buf[2048];
    
    return 0;
}

int fork_proc(){
    from_client = server_handshake( &to_client );
    if(fork()){
        ssread(int from_client);
    }
    else{
        sswrite(int to_client);
    }
}
