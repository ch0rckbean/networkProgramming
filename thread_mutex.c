#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
static pthread_mutex_t the_mutex=PTHREAD_MUTEX_INITIALIZER; 
//1번째 순서. <<pthread.h> 
int x=0;

void *start_thread(void *message){
    int t;
    for(;;){
        pthread_mutex_lock(&the_mutex); //임계영역 여기 ~

        t=x;
        t=t+1;
        printf("%s%d\n", (const char*)message,t);
        sleep(1);
        x=t;

        pthread_mutex_unlock(&the_mutex); //임계영역 ~여기
    }
}

int main(void){
    pthread_t t1,t2;
    const char *message1="Thread 1: ";
    const char *message2="Thread 2: ";

    pthread_create(&t1,NULL, start_thread, (void*)message1);
    pthread_create(&t2, NULL, start_thread, (void*)message2);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}