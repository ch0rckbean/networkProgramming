#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//execl: 경로 파일 메모리 로드-> 현 실행 중 이미지 대체
// #include <unistd.h>
// int execl(const char *path, const char *arg,..,NULL);
int main(void){
    //현재 실행 중 프로그램 /bin/vi로 대체
    int ret;
    ret=execl("/bin/ls","ls","-l",NULL); //끝 마킹
    if(ret ==-1){
        perror("execl");
    }
    return 1;
}