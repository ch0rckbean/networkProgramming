#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h> //for struct serv

void main(void){
    const char *service="http";
    const char *proto="tcp";
    short port=80;
    struct servent *serv;

    serv=getservbyname(service, proto); //name, proto
    printf("Official Service Name: %s\n",serv->s_name);
    printf("port Number: %d\n",serv->s_port);
}
