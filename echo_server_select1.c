//https://github.com/apress/def-guide-to-linux-network-programming

#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 1024
#define PORTNUM 3500
#define SOCK_SETSIZE 1021

int main(int argc, char **argv){
    int server_fd, client_fd;
    socklen_t addrlen;
    int fd_num;
    int maxfd=0;
    int sockfd;
    int t=0;
    char buf[MAXLINE];
    fd_set readfds, allfds;

    struct sockaddr_in server_addr,client_addr; //구조체 생성

    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==-1){ //소켓 생성
        perror("socket error");
        return 1;
    }
    //초기화 및 정보 지정
    memset((void *)&server_addr,0x00,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(PORTNUM);

    //bind
    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
        perror("bind error");
        return 1;
    }
    //listen
    if(listen(server_fd,5)==-1){
        perror("listen error");
        return 1;
    }

// ----------------------------------
    FD_ZERO(&readfds); //초기화
    FD_SET(server_fd,&readfds); //검사 파일 목록 추가
    maxfd=server_fd;

    while(1){
        allfds=readfds; //copy
        printf("Select Wait %d\n",maxfd);
        fd_num=select(maxfd+1,&allfds,(fd_set*)0,
                        (fd_set*)0,NULL); //입출력 이벤트 대기
        if(FD_ISSET(server_fd,&allfds)){
            addrlen=sizeof(client_addr);
            client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addrlen);

            FD_SET(client_fd,,&readfds);

            if(client_fd>maxfd){
                maxfd=client_fd;
                printf("Accept OK\n");
                continue;
            }
            for(i=0; i<=maxfd; i++){
                sockfd=i;
                if(FD_ISSET(sockfd,&allfds)){
                    memset(buf,0x00,MAXLINE);
                    if(read(sockfd,buf,MAXLINE)<=0){
                        close(sockfd);
                        FD_CLR(socfd,&readfds);
                    }else{
                        if(strncmp(buf,"quit\n",5)==0){
                            close(sockfd);
                            FD_CLR(sockfd,&readfds);
                            break;
                        }
                    printf("Read: %s",buf);
                    write(sockfd,buf,strlen(buf));
                    }
                    if(--fd_num<=0){
                        break;
                    }
                }
            }
        }
    }
}