#include <stdio.h>
#include <unistd.h>
#include <signal.h>


/*시그널이 발생했을때 호출되어야 할 함수가 각각 정의되어있다.
이러한 유형의 함수를 가리켜 시그널 핸들러라 한다.
*/
void timeout(int sig)
{
    if(sig==SIGALRM)
        puts("Time out!");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig==SIGINT)
        puts("CTRL+C pressed");
}


int main(int argc, char *argv[])
{
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for(i=0; i<3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}