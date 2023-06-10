#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#define SERVERPORT 8888
#define MAXBUF 1024

int main(){
	int sock1, sock2;
	int addrlen;
	struct sockaddr_in xferServer, xferClient;
	int returnStatus;

//소켓1 생성 => server bind() => 소켓1 listen() =>
//=> client accept() 하는 소켓2 (client size 주소값으로)
//=> 소켓2가 받아온 filename read() =file open() => 소켓2로 write()

/*Create a socket*/
	sock1=socket(AF_INET, SOCK_STREAM,0);
	if(sock1==-1){
		fprintf(stderr, "Could not create socket!\n");
		exit(1);
	}
/*Bind to socket*/
	xferServer.sin_family=AF_INET;
	xferServer.sin_addr.s_addr=INADDR_ANY;
	xferServer.sin_port=htons(SERVERPORT);

	returnStatus=bind(sock1,(struct sockaddr*)&xferServer,
						sizeof(xferServer)); //소켓1, 구조체, 서버 크기
	if(returnStatus==-1){
		fprintf(stderr, "Could not bind to socket!\n");
		exit(1);
	}
/*listen*/
	returnStatus=listen(sock1,5);
	if (returnStatus == -1){
		fprintf(stderr, "Could not listen on socket!\n");
		exit(1);
	}

/*Connnection Queue*/
	for(;;){
		int fd;
		int i, readCounter, writeCounter;
		char* bufptr;
		char buf[MAXBUF];
		char filename[MAXBUF];
/*wait for connection*/
		addrlen=sizeof(xferClient);
/*accept*/
	sock2=accept(sock1, (struct sockaddr*)&xferClient,&addrlen);
	//소켓1, 구조체, 서버 크기 주소값
	if (sock2 == -1){
		fprintf(stderr, "Could not accept connection!\n");
		exit(1);
		}
/*get the filename*/
	i=0;
	if((readCounter=read(sock2,filename+i, MAXBUF))>0){
		i+=readCounter;
	}
	if(readCounter==-1){
		fprintf(stderr, "Could not read filename from socket!\n");
		close(sock2);
		continue;
	}
	filename[i+1]='\0';
	printf("Reading file %s\n",filename);

/*open file for reading*/
	fd=open(filename,O_RDONLY);
	if(fd==-1){
		fprintf(stderr, "Could not open file for reading!\n");
		close(sock2);
		continue;
	}
/*reset the read counter*/
	readCounter=0;
/*send to client*/
	while((readCounter=read(fd,buf,MAXBUF))>0){
		writeCounter=0;
		bufptr=buf;
		while(writeCounter<readCounter){
			readCounter-=writeCounter;
			bufptr+=writeCounter;
			writeCounter=write(sock2, bufptr,readCounter);

			if(writeCounter==-1){
				fprintf(stderr, "Could not write file to client!\n");
				close(sock2);
				continue;
			}
		}
	}
		close(sock2);
		close(fd);
	}
	close(sock1);
	return 0;
}