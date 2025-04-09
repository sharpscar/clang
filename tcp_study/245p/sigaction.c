#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void timeout(int sig)
{
    if(sig==SIGALRM)
        puts("TIME out!");
        
    alarm(2);
}

int main(int argc, char* argv[])
{
    int i;
    struct sigaction act;

    /*시그널 발생시 호출될 함수의 등록을 위해서는 이렇듯 sigaction구조체 변수를 선언해서
    멤버 sa_handler에 함수 포인터갑을 저장해야한다.*/
    act.sa_handler=timeout;
    /*앞서 sigaction 구조체를 설명하면서 멤버 sa_mask의 모든비트를 0으로 초기화해야 한다고 하였다.
    sigemptyset함수는 바로 이러한 목적으로 호출되는 함수이다.*/
    sigemptyset(&act.sa_mask);

    
    act.sa_flags=0;
    sigaction(SIGALRM, &act,0);
    
    

    alarm(2);

    for(i=0; i<3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}