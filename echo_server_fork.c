#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define MAXLINE 1024
#define PORTNUM 3500

int main(int argc, char **argv){
    int server_fd, client_fd;
    pid_t pid;
    socklen_t addrlen;
    int readn;
    char buf[MAXLINE];
    struct sockaddr_in client_addr, server_addr;

    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0){
        return 1;
    }
    memset((void*)&server_addr,0x00,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(PORTNUM);

    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
    {
        perror("bind error");
        return 1;
    }
    if(listen(server_fd,5)==-1){
        perror("listen error");
        return 1;
    }
    signal(SIGCHLD, SIG_IGN);
    while(1){
        addrlen=sizeof(client_addr);
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addrlen);
        if(client_fd==-1){
            printf("accept error\n");
            break;
        }
        pid=fork();
        if(pid==0){ //child
            memset(buf, 0x00, MAXLINE);
            while((readn=read(client_fd,buf,MAXLINE))>0){
                printf("Read Data: %s\n",buf);
                inet_ntoa(client_addr.sin_addr);
                write(client_fd,buf,strlen(buf));
                memset(buf, 0x00, MAXLINE);
            }
            close(client_fd);
            return 0;
        }
    }
    close(server_fd);
    return 0;
}
