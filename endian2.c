#include <stdio.h>

void main(void){
    int x=0x12345678;
    int *addr; //포인터 선언
    addr=&x; //x의 주소값 가리킴
    printf("%x %x %x %x\n",
    *(unsigned char*)addr, //주소 내 값
    *((unsigned char*)addr+1), //1칸 이동 후 주소 내 값
    *((unsigned char*)addr+2),
    *((unsigned char*)addr+3));
}