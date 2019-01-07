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

int fork_proc(){
    from_client = server_handshake( &to_client );
    if(fork()){
        ssread();
    }
    else{
        sswrite();
    }
}
