#include <stdio.h>
#include <stdlib.h> //for exit
#include <string.h> //for strlen
#include <netdb.h> //for AF_INET
#include <sys/socket.h> //for socket
#include <sys/types.h>
#include <unistd.h> 
//server +
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define BUF_SIZE 256

//서버 구조체 생성 => 소켓 생성 => 구조체 0으로
//서버 구조체에 connect() => read() 

int main(int argc, char *argv[]){
    int simpleSocket=0;
    int simplePort=0;
    int returnStatus=0;
    char buffer[BUF_SIZE]="";

    struct sockaddr_in simpleServer;
    if(3!=argc){
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }

/*Create a streaming socket*/
    simpleSocket=socket(AF_INET, SOCK_STREAM, 0); 
    if(simpleSocket==-1){
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else{
        fprintf(stderr, "Socket created!\n");
    }

/*Retrieve port number for connecting*/
    simplePort=atoi(argv[2]);

/*Set up the address structure*/
    bzero(&simpleServer,sizeof(simpleServer));
    simpleServer.sin_family=AF_INET;
    inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
    simpleServer.sin_port=htons(simplePort);

/*Connect to address, port*/
    returnStatus=connect(simpleSocket, 
        (struct sockaddr *)&simpleServer,
        sizeof(simpleServer)); //소켓, 서버 구조체, 구조체 크기
    if (returnStatus==0){
        fprintf(stderr, "Connect successful!\n");
    }
    else{
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }

/*Get the message from the server*/
    returnStatus=read(simpleSocket, buffer, sizeof(buffer));
    //소켓, 버퍼, 버퍼 크기
    if(returnStatus>0){
        printf("%d: %s", returnStatus, buffer);
    }
    else{
        fprintf(stderr, "Return status=%d\n", returnStatus);
    }
    close(simpleSocket);
    return 0;
}