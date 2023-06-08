#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void){
    int fd;
    extern int errno; //<errno.h>
    errno=0;
    if(fsync(fd)==-1){
        perror("fsync"); //<stdio.h>
        //write function name as argument
    }
    printf("%d\n",errno);
}