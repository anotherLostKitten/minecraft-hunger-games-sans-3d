#include <fcntl.c>
#include <unistd.h>
#include "render.h"

int from_server, to_server;

int clwrite(){
    int buf[2048];
    exit(0);
}
int clread(){
    int buf[2048];
    exit(0);
}

int client(){
    from_server = client_handshake(*to_server);
    if(fork()) clread();
    if(fork()) clwrite();
    setupSDL();

    return 0;
}
