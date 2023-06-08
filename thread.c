#include <sys/types.h>
#include <stdio.h>
// #include <stdlib.h>
#include <pthread.h> //for creating pthread

//#include <pthread.h>
// int pthread_create (pthread_t *thread,
// const pthread_attr_t *attr,
// void *(*start_thread) (void *),
// void *arg);
//스레드 2개 생성 + 값 넘기기
void *start_thread(void *message){
    printf("%s\n",(const char*)message);
    return message;
}

int main(void){
    pthread_t thing1, thing2; //<pthread.h>
    const char *message1="Thing 1";
    const char *message2="Thing 2";

    pthread_create(&thing1,NULL,start_thread,(void*)message1);
    pthread_create(&thing2,NULL,start_thread,(void*)message2);

    //스레드 종료 후 join 호출해야만 자원 회수 가능
    //pthread_join(pthread_t thead, void **retval)
    pthread_join(thing1,NULL); 
    pthread_join(thing2,NULL);
    return 0;
}