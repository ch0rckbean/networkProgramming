#include <sys/types.h>
#include <stdlib.h>

int main(void){
    system("ls -l");
    system("pidof bash"); //이 프로세스 저장 x, 그때그때 새롭게 생성
    return 0;
}