#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int status;
    /**생성된 자식프로세스는 리턴문 실행을 통해 종료하게 된다. */
    pid_t pid=fork();
    if(pid==0)
    {
        return 3;
    }
    else{
        printf("Child PID : %d \n", pid);

        /*생성된 자식 프로세스는 아래 exit(7)에서 보이듯 종료됨*/
        pid=fork();
        if(pid==0)
        {
            exit(7);
        }else{
            printf("Child PID: %d \n", pid);
            /**웨잇 함수 호출로 인해 종료된 프로세스 관련 정보는 status에 담기게 되고
             * 해당 정보의 프로세스는 완전히 소멸된다.
             */
            wait(&status);

            /**WIFEXITED매크로 함수를 통해자식프로세스의 정상종료 여부를 확인하고 있다. 그리고 정상
             * 종료인경우에 한하여 WEXITSTATUS함수를 호출하여 자식프로세스가 전달한 값을 출력하고 있다.
             */
            if(WIFEXITED(status))
                printf("Childsend one: %d \n", WEXITSTATUS(status));
            /** 앞서 생성한 자식 프로세스가 두 개 이므로 한번의 wait함수 호출과 매크로 함수의 호출을 진행하고 있다.*/
            wait(&status);
            if(WIFEXITED(status))
                printf("Child send two: %d \n", WEXITSTATUS(status));

            /**부모 프로세스의 종료를 멈추기 위해서 삽입한 코드이다 이 순간에 여러분은 자식 프로세스의 상태를 확인하면 된다. */
            sleep(30);

        }
        
    }
}