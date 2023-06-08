#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
    pid_t pid;
    pid=fork();

    if(pid>0){
        printf("Parent. myPid=%d\n",getpid());
        sleep(6);
    }
    else if(!pid){
        printf("Child. myPid=%d\n",getpid());
    }
    else if(pid ==-1){
        perror("fork");
    }
    return 1;
}