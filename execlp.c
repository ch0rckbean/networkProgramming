#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void){
    int ret;
    ret=execlp("ls","ls","-l",NULL); //file, arg ..
    if(ret==-1){
        perror("execlp");
    }
    return 1;
}