#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "sockets.h"

    void error_check(int i,char*s){
        if(i<0){
            printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
            exit(1);
        }
    }

    /*creates, binds a server side socket
      and sets it to the listening state*/
    int server_setup(){
        int sd,i;
        sd=socket(AF_INET,SOCK_STREAM,0);
        error_check(sd,"server socket");
        struct addrinfo*hints,*results;
        hints=calloc(1,sizeof(struct addrinfo));
        hints->ai_family=AF_INET;  //IPv4 address
        hints->ai_socktype=SOCK_STREAM;  //TCP socket
        hints->ai_flags=AI_PASSIVE;  //Use all valid addresses
        getaddrinfo(NULL,PORT,hints,&results);
        i=bind(sd,results->ai_addr,results->ai_addrlen);
        error_check(i,"server bind");
        i=listen(sd,10);
        error_check(i,"server listen");
        free(hints);
        freeaddrinfo(results);
        return sd;
    }


    /*sd should refer to a socket in the listening state 
      runs the accept call returns the socket descriptor for the new socket connected to the client.*/
    int server_connect(int* sd){
        int client_socket;
        socklen_t sock_size;
        struct sockaddr client_address;
        sock_size=sizeof(client_address);
        client_socket=accept(*sd,&client_address,&sock_size);
        error_check(client_socket,"server accept");
        return client_socket;
}

/*to_server is a string representing the server address
  create and connect a socket to a server socket that is in the listening state
  returns the file descriptor for the socket*/
int client_setup(char*server){
	int sd,i;
	sd=socket(AF_INET,SOCK_STREAM,0);
	error_check(sd,"client socket");
	struct addrinfo*hints,*results;
	hints=calloc(1,sizeof(struct addrinfo));
	hints->ai_family=AF_INET;  //IPv4
	hints->ai_socktype=SOCK_STREAM;  //TCP socket
	getaddrinfo(server,PORT,hints,&results);
	i=connect(sd,results->ai_addr,results->ai_addrlen);
	error_check(i,"client connect");
	free(hints);
	freeaddrinfo(results);
	return sd;
}
