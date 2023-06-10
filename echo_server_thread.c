#include <pthread.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h> //inet_ntoa
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1024
#define PORTNUM 3500

void *thread_func(void *data){
    int sockfd=*((int *)data);
    int readn;
    socklen_t addrlen;
    char buf[MAXLINE];
    struct sockaddr_in client_addr;
    memset(buf,0x00,MAXLINE);
    addrlen=sizeof(client_addr);
    getpeername(sockfd, (struct sockaddr*)&client_addr,&addrlen);
    
    while((readn=read(sockfd,buf,MAXLINE))>0){
        printf("Read Data %s(%d):%s",
                inet_ntoa(client_addr.sin_addr),
                ntohs(client_addr.sin_port),
                write(sockfd,buf,strlen(buf))
            );
        }
    close(sockfd);
    printf("worker thread end\n");
    return 0;
}

int main(int argc, char **argv){
    int server_fd,client_fd;
    socklen_t addrlen;
    int readn;
    char buf[MAXLINE];
    pthread_t thread_id;

    struct sockaddr_in server_addr,client_addr;
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        return 1;
    }
    memset((void*)&server_addr,0x00,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(PORTNUM);

    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
        perror("bind error");
        return 1;
    }
    if(listen(server_fd,5)==-1){
        perror("listen error");
        return 1;
    }

    for(;;){
        addrlen=sizeof(client_addr);
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addrlen);
        if(client_fd==-1){
            printf("accept error\n");
        }
        else{
            pthread_create(&thread_id,NULL,thread_func,(void *)&client_fd);
            pthread_detach(thread_id);
        }
    }
    return 0;
}