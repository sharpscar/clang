#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    int fds[2];
    char str1[]="Who are you?";
    char str2[]="Thank you for your message";  
    char buf[BUF_SIZE];    
    pid_t pid;

    pipe(fds);
    pid=fork();
    if(pid==0)
    {
        /*
        자식 프로세스의 실행 영역이다. 아래 행을 통해서 데이터를 전송도 하고 19행을 통해서 
        데이터를 수신도 한다 read 특히 18행의 sleep함수 호출에 주목하기 바란다.
        
        */
        write(fds[1], str1, sizeof(str1));
        // sleep(2);
        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    }
    else
    {
        /**부모 프로세스의 실행영역이다. read함수 구문.. 통해서 데이터를 수신하는데
         * 이는 위의 자식프로세스가 전송하는 데이터를 수신하기 위함이다. 그리고 write함수구문을 통해서
         * 데이터를 전송하는데 이는  25행의 read문을 통해서 자신프로세스에게 수신이 된다.
         */
        read(fds[0], buf, BUF_SIZE);
        printf("Parent proc output: %s \n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3); // 이부분을 주석처리하라!
    }
    return 0;
}