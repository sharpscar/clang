#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    pid_t pids[10];
    pid_t pid;

    for(int i=0;i<10;i++)
    {
        pid= fork();
        if(pid)
        {
            pids[i] = pid;
        }else{
            srand(i);
            int r = (rand() % 7 )+3;
            printf("%d번 프로세스는 %d초간 살아있는다 . \n", i, r);
            sleep(r);
            printf("%d번 프로세스는 죽었다.\n", i);
            exit(1);
        }
    }

    int status;
    pid_t ended_pid;
    while((ended_pid = wait(&status))>0){
        int child_index = WEXITSTATUS(status);
        printf("[부모] PID=%d 자식 프로세스 종료 감지(PID=%d, index=%d)\n",
        getpid(),ended_pid, child_index);
    }
    printf("모든 프로세스가 종료되었다.\n");
    return 0;
}