#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> //exit

int main(void){
    pid_t pid;
    int i=100;
    pid=vfork();

    if(pid>0){
        printf("P: i==%d\n",i);
    }
    else if(!pid){
        i+=20;
        printf("C: i==%d\n",i);
        exit(0); //<stdlib.h>
    }
    else if(pid==-1){
        perror("vfork");
    }
    return 1;
}