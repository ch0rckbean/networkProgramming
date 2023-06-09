#include <sys/socket.h> //for socket
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h> //for exit
#include <string.h> //for strlen
#include <unistd.h>
#include <netdb.h> //for AF_INET

const char APRESSMESSAGE[]="APRESS - For Professionals, By Professionals.\n";
int main(int argc, char* argv[]){
    int simpleSocket=0;
    int simplePort=0;
    int returnStatus=0;

    struct sockaddr_in simpleServer; //구조체 생성
    if(2!=argc){
        fprintf(stderr, "Usage: %s <port>\n",argv[0]);
        exit(1); //<stdlib.h>
    }

/*1.Create a Socket*/
    simpleSocket=socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(simpleSocket==-1){
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else{
        fprintf(stderr, "Socket created\n");
    }

/*Set up address structure*/
    simplePort=atoi(argv[1]);
    bzero(&simpleServer,sizeof(simpleSocket)); //생성한 구조체를 simpleSocket 길이만큼 0으로 채워줌
    simpleServer.sin_family=AF_INET;
    simpleServer.sin_addr.s_addr=htonl(INADDR_ANY);
    simpleServer.sin_port=htons(simplePort);

/*2.Bind to the address , IP */
    returnStatus=bind(simpleSocket, 
        (struct sockaddr *)&simpleServer, 
        sizeof(simpleServer));

    if (returnStatus==0){
        fprintf(stderr, "Bind completed!\n");
    }
    else{
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

/*3.Listen for connections*/
    returnStatus=listen(simpleSocket,5);
    if(returnStatus==-1){
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(1);
    }

    while(1){
        struct sockaddr_in clientName={0};
        int simpleChildSocket=0;
        int clientNameLength=sizeof(simpleChildSocket);
/*4.Wait here*/
        simpleChildSocket=accept(
            simpleSocket, 
            (struct sockaddr*)&clientName,
            &clientNameLength
        );
        if(simpleChildSocket==-1){
            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);
        }
    
        write(simpleChildSocket,APRESSMESSAGE,strlen(APRESSMESSAGE));
        close(simpleChildSocket);
    }
    close(simpleSocket);
    return 0;
}