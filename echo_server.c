#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXBUF 1024
#define PORTNUM 3500

//소켓, 클라이언트 구조체 생성 => 소켓 생성, 서버 구조체 0으로
// => 서버 소켓 bind(), listen() => 클라 구조체 accept()
//=>클라 소켓 read() => 클라 소켓 write()

int main(int argc, char **argv){
    int server_sockfd, client_sockfd;
    int client_len, n;
    char buf[MAXBUF];
    struct sockaddr_in clientaddr, serveraddr;
    client_len=sizeof(clientaddr);

    server_sockfd=socket(AF_INET,SOCK_STREAM,IPROTO_TCP);
    if (server_sockfd==-1){
        perror("socket error: ");
        exit(0);
    }
    
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(PORTNUM);

    bind(server_sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(server_sockfd,5);

    for(;;){
        memset(buf,0x00,MAXBUF);
        client_sockfd=accept(server_sockfd,
            (struct socketaddr*)&clientaddr, 
            &client_len); //서버 소켓, 클라 구조체, 클라 구조체 크기
        printf("New Client connect: %s\n", 
                inet_ntoa(clientaddr.sin_addr));
        if((n=read(client_sockfd,buf,MAXBUF))<=0){
            close(client_sockfd);
            continue;
        }
        printf("Read Data: %s\n",buf);
        if(write(client_sockfd,buf,MAXBUF)<=0){
            perror("write error: ");
            close(client_sockfd);
        }
        close(client_sockfd);
    }
    close(server_sockfd);
    retuen 0;    
}