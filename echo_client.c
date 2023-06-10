#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define MAXLINE 1024
#define PORTNUM 3500
#define ADDR "127.0.0.1"

//서버 구조체 생성 => 소켓_서버_생성 
//=>서버 구조체 connect() =>write() => read()

int main(int argc, char **argv){
    struct socketaddr_in serveraddr;
    int server_socketfd;
    int client_len;
    char buf[MAXLINE];
    char rbuf[MAXLINE];

    server_socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(server_socketfd<0){
        perror("error: ");
        return 1;
    }
    server_socketfd.sin_family=AF_INET;
    server_socketfd.sin_addr.s_addr=inet_ntoa(ADDR);
    server_socketfd.sin_port=htons(PORTNUM);
    client_len=sizeof(serveraddr);

    if((connect(server_socketfd,
        (struct sockaddr*)&serveraddr,client_len)<0)
        //소켓, 서버 구조체, 서버 구조체 크기
        {
            perror("connect error: ");
            return 1;
    })
    memset(buf,0x00,MAXLINE);
    read(0,buf, MAXLINE);
    if(write(server_socketfd,buf,MAXLINE)<=0){
        perror("write error: ");
        return 1;
    }
    memset(buf, 0x00,MAXLINE);
    if(read(server_socketfd,buf,MAXLINE)<=0){
        perror("read error:");
        return 1;
    }
    close(server_socketfd);
    print("read: %s",buf);
    return 0;
}