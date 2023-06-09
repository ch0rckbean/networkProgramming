#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

void main(void){
    const char *service="http";
    const char *proto="tcp";
    short port=80;
    struct servent *serv;

    serv=getservbyname(service,proto);
    printf("Official Service name: %s\n", serv->s_name);
    printf("port Number: %d\n",ntohs(serv ->s_port));

    serv=getservbyport(htons(port),proto);
    printf("Official Service name: %s\n", serv->s_name);
    printf("port number: %d\n",ntohs(serv->s_port));
}