#include <sys/socket.h>
int Create_Socket(void);
void Init_Server(struct sockaddr_in *server);
int Server_Bind(struct sockaddr_in server, char socket_desc);
int Server_Listen(char socket_desc);
int Server_Messages(char socket_desc, struct sockaddr_in client);
void *Server_Connection_Handler(void *socket_desc);
