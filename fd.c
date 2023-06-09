#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void main(void){
    char buf[]="ABC DE FGHI";
    int fd=open("/dev/pts/0",O_RDWR);
    int ret=write(fd, &buf, strlen(buf));
    close(fd);
}