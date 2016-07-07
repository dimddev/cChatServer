#ifndef CCHAT_CONFIG

typedef struct {
    char *server_name;
    int port;
} Config_T;

Config_T Read_Config(char file_name[], Config_T conf);

#endif
