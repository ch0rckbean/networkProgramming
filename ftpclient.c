#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define SERVER_PORT 21 //10진수니까 byte order 챙겨야 함
#define SERVER "223.194.7.95"
#define MAXBUF 1024 //데이터 수신 시 끊을 단위
#define USER "elec"
#define PASS "comm"
#define FILENAME "welcome.txt"

void error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[])
{
	int ctrlSocket, dataSocket;
	struct sockaddr_in serverAddr; //ip 주소 저장 구조체
	char response[MAXBUF]; //응답 받을 문자열 배열
	char *filename=FILENAME;
	//int returnStatus;
	
/* create ctrl socket */
	ctrlSocket=socket(AF_INET, SOCK_STREAM, 0); //tcp 통신이므로 SOCK_STREAM 사용
	
	//단계별 에러 사항 점검
	if (ctrlSocket < 0) 
	{
		fprintf(stderr, "Could not create socket!\n");
	} 
	else{
		printf("Control Socket created.\n");
	

/* connect to FTP server */
	//구조체 내 정보 할당
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr=inet_addr(SERVER);

	//클라이언트이므로 bind 대신 connect 함수 사용
	if(connect(ctrlSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <0)
	{ 
		perror("Failed to connect to FTP server.\n");
	}
	else{
		printf("Connected to FTP server.\n");
	}
/* receive welcome message */
	//recv(데이터 수신할 소켓의 파일 디스크립터, 버퍼 포인터, 버퍼 크기, 옵션 플래그): 데이터 수신.에러값==-1
	recv(ctrlSocket, response, sizeof(response),0);
	printf("%s\n", response);

/*login*/
	/* send username */	
	sprintf(response, "USER %s\r\n", USER);
	send(ctrlSocket, response, strlen(response), 0);
	recv(ctrlSocket, response, sizeof(response), 0);

	/*send password */
	sprintf(response, "PASS %s\r\n", PASS);
	send(ctrlSocket, response, strlen(response), 0);
	recv(ctrlSocket, response, sizeof(response), 0);

/* enter Passive mode */
	send(ctrlSocket, "PASV\r\n", 6,0);
	recv(ctrlSocket, response, sizeof(response), 0);

/* parse PASV mode response to get data IP and port */
	//ip 주소, 포트 번호 할당 및 선언
	char *ipStart=strchr(response, '(') + 1;
	char *ipEnd=strchr(ipStart, ')');
	*ipEnd='\0'; //데이터 버퍼 저장 후 종료 나타내기 위해 Null 문자 선언
	int ip1,ip2,ip3,ip4,port1,port2;
	sscanf(ipStart, "%d,%d,%d,%d,%d,%d", &ip1, &ip2, &ip3, &ip4, &port1, &port2); //각 변수에 ip, 포트 번호 할당

/* connect to data socket */	
	dataSocket =socket(AF_INET, SOCK_STREAM, 0);
	//단계별 에러 사항 점검
	if(dataSocket < 0)
	{
		perror("Failed to create data socket.\n");
	}
	else
	{
		printf("Created data socket.\n");
	}

/* set dataAddr */
	struct sockaddr_in dataAddr;
	memset(&dataAddr, 0, sizeof(dataAddr));
	dataAddr.sin_family = AF_INET;
	dataAddr.sin_port = htons(port1 * 256 + port2); //PASV mode 접속 시 각각 16진수 변환 => 두 개 붙여 10진수 변환

	if (inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)&ip1), &(dataAddr.sin_addr)) <= 0)
	{//네트워크 바이트 오더의 32비트 값 => Dotted Decimal Notation
		printf("Failed to connect to data socket.\n");
	} 
	else {
    		printf("Connected to data socket.\n");
	}

/* send retrieve command */
	sprintf(response, "RETR %s\r\n", filename); //데이터를 서버로부터 retrieve 해 옴. FTP에서는 GET보다 RETR 사용
	send(ctrlSocket, response, strlen(response),0);
	recv(ctrlSocket, response, sizeof(response), 0);

/* open local file for writing */
	int bytesRead;
	char buffer[MAXBUF];

	FILE *file=fopen(filename, "w");
	if(file==NULL){
		perror("Falied to open file for writing.\n");
		exit(1);
	}

/* receive and write file data */
	while ((bytesRead = recv(dataSocket, buffer, sizeof(buffer)-1,0)) > 0)
	{
		buffer[bytesRead]='\0';
		printf("%s",buffer);		
		fflush(stdout);
		fwrite(buffer, 1, bytesRead, file);
	}
	
/* close file and data socket */
	fclose(file);
	close(dataSocket);

/* receive transfer complete message */
	recv(ctrlSocket, response, sizeof(response), 0);
	printf("%s\n", response);
	
/*cleanup*/
	close(ctrlSocket);
	return 0;
	}
}

