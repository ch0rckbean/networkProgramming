#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void){
    int ret;
    ret=execvp("vi","vi","/home/kidd/hooks.txt","NULL");
    //vi 실행 위해 execvp( ) 사용
    //const char *__file, char *const __argv[]
    if(ret==-1){
        perror("execvp");
    }
    return 1;
}