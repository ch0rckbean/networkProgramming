#include <sys/types.h>
#include <sys/wait.h> //for wait
#include <unistd.h>
#include <stdio.h>

int main(void){
    int status;
    pid_t pid;
    
    if(!fork()){
        printf("Child PID=%d\n",getpid());
        sleep(10);
        return 1;
    }
    pid=wait(&status); //callByReference로 status 내 기록

    if(pid==-1){
        perror("wait");
    }
    printf("Parent PID=%d, wait() return pid=%d\n",getpid(),pid);

    if(WIFEXITED(status)){ //WIFEXITED: WEXITSTATUS
        printf("Normal Termination with exit status=%d\n",WEXITSTATUS(status));
    }
    if(WIFSIGNALED(status)){ //WIFSIGNALED : WTERMSIG
        printf("Killed by signal=%d%s\n",WTERMSIG(status),WCOREDUMP(status)? "(dumped core)": "");
    }
    return 0;
}