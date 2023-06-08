#include <sys/types.h>
#include <unistd.h> //for sys calling
#include <stdio.h>

int main(void){
    printf("My pid=%d\n", getpid());
}