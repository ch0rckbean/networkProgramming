#include <stdio.h>

void main(void){
    union endian{ //구조체와의 차이: 멤버들 시작 주소 다 같음(overlap)
        unsigned char c;
        unsigned short s;
        unsigned int i;
    };
    union endian e;
    e.i=0x12345678;
    printf("%x %x %x\n",e.c, e.s, e.i);
}
