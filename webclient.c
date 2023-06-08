#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* define host,port to what you want */
#define HOST "223.194.7.95" //host num 미리 정의
#define PORT 80 //port num 미리 정의

#define MAXBUF 1024 //최대 buffer 값을 1024로 정의

int main(int argc, char* argv[])  
//argc: argument의 개수 argv:argument들을 저장하는 문자열 배열
	{
	int  socketfd; //소켓 변수  선언. 성공/실패 값이 정수로 전달되기에 int 사용
	int returnStatus; //반환 상태 변수
	struct sockaddr_in serverAddr; //ip주소를 저장하는 구조체 선언 
	char request[MAXBUF]; //요청을 저장할 MAXBUF 크기의 문자열 배열
	char response[MAXBUF]; //응답을 저장할 MAXBUF 크기의 문자열 배열

	if (argc<3) //argument 개수가 3보다 작을 때
	{ //argument 형식 출력 후 즉시 종료
		fprintf(stderr, "Usage: %s <ip address> <port>\n",argv[0]);
		exit(1);
	}

/* create a socket */
	socketfd=socket(AF_INET, SOCK_STREAM, 0); 
	//domain: Address Faminly Internet
	//type: TCP 소켓 생성을 위해 SOCK_STREAM 사용
	//protocol: 적합한 프토토콜 자동 선택 위해 0 사용
	if (socketfd==-1) //error 값인 -1을 반환한다면
	{
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}
	else {printf("Socket created!\n");}

/* assign client address */
/* put variables of adrress and port you assigned above*/
	serverAddr.sin_family=AF_INET; //serverAddr구조체에 AF_INET 할당
	serverAddr.sin_port=htons(PORT); //serverAddr 구조체에 port num 할당
	//htons: 호스트 바이트 순서 => 네트워크 바이트 순서 변환
	if(inet_pton(AF_INET, HOST, &(serverAddr.sin_addr))<=0){
	//inet_pton(주소 체계,변환할 호스트 주소 문자열, 바이너리 주소 저장될 메모리 공간): 호스트 주소 => 바이너리 형식 
		perror("Invalid address");
		exit(1);
	}
	else{printf("Valid address\n");}

/*connect to the server */
	if(connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))==-1){
		perror("Failed to connect");
		exit(1);
	}
	else{
		printf("Connected to server");
	}

/* create HTTP request */
	snprintf(request, sizeof(request), "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", HOST);
	//snprintf(생성 문자열 저장 포인트 버퍼, 버퍼 크기, 문자열): 지정된 형식 따라 문자열 생성 후 버퍼에 저장
	//CRLF 위해 \r\n 사용

/* send request to server */
	ssize_t sentBytes=send(socketfd, request, strlen(request),0);
	//send(데이터 전송할 소켓 파일 디스크립터, 전송 데이터, 전송 데이터 크기, 옵션 지정 플래그) : 데이터 => 서버 전송
	if(sentBytes < 0){
		perror("Failed to send request");
		exit(1);
	}
	else{printf("Sent Successfully\n");}

/* receive response from server */
	ssize_t receivedBytes=recv(socketfd, response, sizeof(response)-1, 0);
	//recv(데이터 수신할 소켓의 파일 디스크립터, 버퍼 포인터, 버퍼 크기, 옵션 플래그): 데이터 수신.에러값==-1
	if (receivedBytes < 0){
		perror("Failed to reveive response");
		exit(1);
	}
	else{printf("Received Successfully\n");}

	response[receivedBytes]='\0'; //데이터 버퍼 저장 후 종료 나타내기 위해 Null 문자 추가
	printf("%s",response); //응답 출력

/* cleanup */
	close(socketfd); //소켓 닫기
	return 0;
}
