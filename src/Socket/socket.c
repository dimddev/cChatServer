#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "../../inc/Socket/socket.h"

void Init_Server(struct sockaddr_in *server) {
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = INADDR_ANY;
    server->sin_port = htons(8888);
}

int Create_Socket(void) {

    char socket_desc;

    if((socket_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1) {

        printf("Could not create socket\n");
        exit(1);

    } else {
        return socket_desc;
    }

}

int Server_Bind(struct sockaddr_in server, char socket_desc) {

    if( bind(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }

    return 0;
}

int Server_Listen(char socket_desc) {

    if((listen(socket_desc , 3)) == 0) {
        return 0;

    } else {
        return -1;
    }
}


void *Server_Connection_Handler(void *socket_desc) {

    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];

    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));

    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
    }

    if(read_size == 0) {

        puts("Client disconnected");
        fflush(stdout);

    } else if(read_size == -1) {
        perror("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}

int Server_Messages(char socket_desc, struct sockaddr_in client) {

    int c, client_sock, *new_sock;
    c = sizeof(struct sockaddr_in);

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {

        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;

        if(pthread_create( &sniffer_thread , NULL ,  Server_Connection_Handler , (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}
