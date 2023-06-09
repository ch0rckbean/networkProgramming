#include <stdio.h>
#include <unistd.h>

void main(void){
    char hostname[256];
    int ret;

    ret=gethostname(hostname,256);
    printf("Host name: %s\n",hostname);
}