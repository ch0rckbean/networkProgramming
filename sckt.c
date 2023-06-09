#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>

void main(void){
    int socket_fd;
    socket_fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("Socket Descriptor: %d\n",socket_fd);
    getchar(); //버퍼에 데이터 있을 때 가장 앞 데이터 반환
    close(socket_fd);
}