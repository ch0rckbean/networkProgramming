#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void child_func(int childnum); //인자만큼 fork해 prcs생성

int main(int argc, char *argv[])
{
    int nchildren = 1;
    int pid;
    int x;

    if (argc > 1) {
        nchildren = atoi(argv[1]);
    }
    
    for (x = 0; x < nchildren; x++) {
        if ((pid = fork()) == 0) {//child
            child_func(x + 1);
            exit(0);
        }
    }

    wait(NULL); 
    //fork 시 좀비 prcs 방지 => 자식 prcs 리턴 값 보기

    return 0;
}

void child_func(int childnum)
{
    int sock;
    struct sockaddr_in sAddr;
    char buffer[25];
    int x;

    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = INADDR_ANY; //?
    sAddr.sin_port = 0; //?
    
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(sock, (const struct sockaddr *) &sAddr, sizeof(sAddr));
    
    sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sAddr.sin_port = htons(1972);
    
    //bind 후 connect?
    if (connect(sock, (const struct sockaddr *) &sAddr, sizeof(sAddr)) != 0) {
      perror("client");
      return;
    }
      
    snprintf(buffer, 128, "data from client #%i.", childnum);
    //0: 플래그 세팅 x
    //snprintf: 문자열에 씀. 사이즈 정해줌. str num prnt format
    sleep(1);
    //printf: stdout 에, fprintf: 파일I/O에
    printf("child #%i sent %i chars\n", childnum, send(sock, buffer, strlen(buffer), 0));
    //write 대신 send
    sleep(1);
    printf("child #%i received %i chars\n", childnum, recv(sock, buffer, 25, 0));
    //read 대신 recv
    sleep(1);
    //w: fd, buffer, size
    //send: flag O (정밀함수)
    //w/r: 그냥 보냄, send: flag 통해 조절하며 보냄
    //r/w: write 끝나면 w한 byte수 반환
    //      pthread_create: r/w 전용 함수
    
    close(sock);
}