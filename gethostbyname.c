#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
//for inet_ntoa
#include <netinet/in.h>
#include <arpa/inet.h>

void main(void){
    const char *dns="www.kr.ac.kr";
    struct hostent *host;
    struct in_addr addr;

    host=gethostbyname(dns);

    printf("Official name: %s\n",host -> h_name);
    printf("aliases name: %s\n", host->h_aliases[0]);
    addr.s_addr=*(u_long*)host -> h_addr_list[0];

    printf("ip Addr: %s\n", inet_ntoa(addr));
}