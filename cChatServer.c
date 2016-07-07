/*********************************************
* A Lear project
* file: cChatServer.c
* student: Dim Mita Hakini
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "inc/Config/config.h"
#include "inc/Socket/socket.h"


int main(int argc, char *argv[]) {

    printf("CChat starting...\n");

    char config_file[] = "./config/server.json";
    int server_desc;

    Config_T conf;
    struct sockaddr_in server, client;

    if (argc > 1) {

        printf("Argc: %d", argc);
        printf("%s\n", argv[argc]);

    } else {

        conf = Read_Config(config_file, conf);
        printf("%s\n", conf.server_name);
        printf("%d\n", conf.port);

        Init_Server(&server);
        server_desc = Create_Socket();
        Server_Bind(server, server_desc);
        Server_Listen(server_desc);
        Server_Messages(server_desc, client);
    }

    return 0;

}
