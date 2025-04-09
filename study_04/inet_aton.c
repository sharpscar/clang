#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void error_handling(char * message);

int main(int argc, char * argv[])
{
    char *addr="127.232.127.79";
    struct sockaddr_in addr_inet;

    printf("inet함수 호출전\n");
    printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);

    /*성공시 1 실패시 0*/
    if(!inet_aton(addr, &addr_inet.sin_addr))
    {
        error_handling("Conversion error");
    }
    else{
        // inet_aton함수를 실행이 성공했을 경우 아래처럼  addr_inet.sin_add.s_addr 값이 자동으로 변동되었나본데?
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    }
    return 0;
    
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}