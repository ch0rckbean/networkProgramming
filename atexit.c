#include <stdlib.h>
#include <stdio.h>

void out(void){ //정상 종료 시 실행되는 함수
    printf("atexit() succeeded!\n");
}

int main(void){
    if(atexit(out)){ //노말 프로세스 종료 도중 주어진 함수 실행되도록 
        fprintf(stderr,"atexit() failed!");
    }
    return 0;
}