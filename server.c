#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char *argv[])
{
    struct sockaddr_in sAddr;
    int listensock;
    int newsock;
    char buffer[25];
    int result;
    int nread;
    int pid;
    int val;
    listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    val = 1;
    result = setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    // SOL_SOCKET: level 옵션, 프로토콜 들어감
    if (result < 0) {
        perror("server");
        return 0;
    }
    sAddr.sin_family = AF_INET;
    sAddr.sin_port = htons(1972);
    sAddr.sin_addr.s_addr = INADDR_ANY;
    result = bind(listensock, (struct sockaddr *) &sAddr, sizeof(sAddr));
   
    if (result < 0) {
        perror("server");
        return 0;
    }
    result = listen(listensock, 5);
    if (result < 0) {
        perror("server");
        return 0;
    }
    //nserver
    //- 10개 생성 -> shell 나옴: 부모 먼저 죽어서
    //포크 n개 -> wait(block) n개 해야 =>for문
    //bind 시 6개 이상: connection refused
    //하지만, 프로토콜별로 retransmission. 
    //client 쪽에서 대기 시켜줌
    while (1) {
        newsock = accept(listensock, NULL ,NULL);
        nread = recv(newsock, buffer, 25, 0);
        buffer[nread] = '\0';
        printf("%s\n", buffer);
        send(newsock, buffer, nread, 0);
        printf("child process %i finished.\n", getpid());
        close(newsock);
    }
}