#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig==SIGINT)
    {
        printf("비정상 종료\n");

    }else if( sig== SIGCHLD)
    {
        printf("정상 종료\n");
    }
}

int main()
{
   
    struct sigaction act;
    act.sa_handler = timeout; // 주소만 넘김! 함수도 배열화 가능하다!

    /**sa_mask는 모든 비트를 0으로 sa_flags는 0으로 초기화한다 p240*/ 
    sigemptyset(&act.sa_mask);
    act.sa_flags =0;
    /*ctrl +c 가 입력되면 타임아웃을 실행해라! */
    sigaction(SIGINT, &act, 0); 
    /*정상종료 되었어도 타임아웃을 실행해라! */
    sigaction(SIGCHLD, &act, 0);
    pid_t pid;

    pid =fork();
    if(pid){
        sleep(100);
        printf("종료됨!\n");
    }else{
        sleep(3);
    }
    return 0;
}