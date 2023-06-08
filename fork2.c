#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
    pid_t pid; //pid 변수 선언
    pid=fork();

    if(pid>0){
        printf("I am parent. My pid=%d\n",getpid()); //:parent
        sleep(10); //sleep for ps -e
    }
    else if(!pid){
        printf("I am child. My pid=%d\n",getpid()); //child
        sleep(10);
    }
    else if(pid ==-1){
        perror("fork"); //<stdio.h>
    }
    return 1;
}