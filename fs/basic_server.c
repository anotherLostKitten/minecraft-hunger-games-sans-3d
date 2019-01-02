#include "pipe_networking.h"
int main() {

    int to_client;
    int from_client;
    signal(SIGINT,sighandler);
    mkfifo("Gandalf",0644);
    char buf[256];
shandhake:
    from_client = server_handshake( &to_client );

    goto shandhake;
}
