#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char * argv[])
{
    char *addr1="1.2.3.4";
    char *addr2="1.2.3.256";

    /** 성공시 빅 엔디안 으로 변환된32비트 정수값을 리턴한다! 
     * 실패시 INADDR_NONE 요런 객체 리턴
     */
    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr==INADDR_NONE)
    {
        printf("error occured! in addr1 \n");
    }
    else 
    {
        printf("Network ordered integer addr: %#lx \n", conv_addr);

    }
    //다시한번 호출하는데 이번엔 addr2를 넣고 호출
    conv_addr=inet_addr(addr2);
    if(conv_addr==INADDR_NONE)
    {
        printf("error occured in addr2 \n");
    }
    else
    {
        printf("Network ordered integer addr : %#lx \n\n", conv_addr);
    }
}