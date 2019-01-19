#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef SOCKETS
#define SOCKETS

#define BUFFER_SIZE 256
#define PORT "5495"
#define TEST_IP "127.0.0.1"

int server_setup();
int server_connect(int* sd);
int client_setup(char*server);
void error_check(int i,char*s);

#endif
