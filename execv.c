#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
    const char *args[]={"ls","-l",NULL};
    int ret;
    ret=execv("/bin/ls",args);
    //const char *path, char *const argv[]
    if (ret==-1){
        perror("execv");
    }
    return 1;
}