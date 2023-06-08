#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdint.h> //for intmax_t

int main(void){
    printf("My pid=%jd\n",(intmax_t)getpid());
    printf("Parent's pid=%jd\n",(intmax_t)getppid()); 
    //intmax_t: maximum-width signed integer type. %jd와 대응
    return 1;
}