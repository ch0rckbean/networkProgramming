#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <netdb.h>
#include <stdlib.h> //for exit

const char APRESSMESSAGE[]="APRESS - For Professional, by Professionals!\n";
int main(int argc, char *argv[]){
    int simpleSocket=0;
    int simplePort=0;

    if(2!=argc){
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    
/*Create a Socket*/
    simpleSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(simpleSocket==-1){
        perror("socket");
        exit(1);
    }else{
        fprintf(stderr, "Socket Created!\n");
    }
}