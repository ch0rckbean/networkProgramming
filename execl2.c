#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void){
    int ret;
    ret=execl("/bin/ls", "ls", "-l", NULL);
    
    if(ret==-1){
        perror("execl");
    }
    printf("End of execl() test program\n"); //execl로 인해 실행 x
    return 1;
}