#include <stdlib.h>
#include <stdio.h>
#include "../src/cJSON.h"
#include "../../inc/Config/config.h"


Config_T Read_Config(char file_name[], Config_T conf) {

    char *buffer = 0;
    int len;

    FILE *config;

    if((config = fopen(file_name, "r")) == NULL) {

        fprintf(stderr, "%s\n", "Config file does not exist..");
        exit(1);

    } else {

        fseek(config, 0, SEEK_END);
        len = ftell(config);
        fseek(config, 0, SEEK_SET);

        buffer = (char *)malloc(len);

        if (buffer) {
            fread(buffer, 1, len, config);
        }

        fclose(config);

    }

    if (buffer) {

        cJSON *root = cJSON_Parse(buffer);
        cJSON *server_name = cJSON_GetObjectItem(root, "server_name");
        cJSON *port = cJSON_GetObjectItem(root, "port");

        conf.server_name = server_name->valuestring;
        conf.port = port->valueint;

    }

    return conf;
}
