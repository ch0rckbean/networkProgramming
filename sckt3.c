#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h> //for inet_pton 
#include <netinet/in.h> //for AF_INET
#include <strings.h> //for strlen()
#include <stdlib.h>
#define IP "127.0.0.1"

int main(void){
    int sock=0;
    struct sockaddr_in sockaddr;

    sock=socket(AF_INET, SOCK_STREAM, 0);
    if (sock==-1){
        perror("socket");
        exit(0);
    }

    bzero(&sockaddr, sizeof(struct sockaddr_in));
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_port=htons(80);

    if(inet_pton(AF_INET, IP, &sockaddr.sin_addr)!=1){
        perror("inet_pton");
        return 1;
    }
    if (connect(sock, (struct sockaddr*)&sockaddr, 
                    sizeof(struct sockaddr_in))!=0){
        perror("connect");
        return 1;
    }

    return 0;
}