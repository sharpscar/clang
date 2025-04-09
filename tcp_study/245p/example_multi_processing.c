#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
    pid_t pid;  //unsigned int

    pid = fork();  // 메모리를 복사해서 옆에다 놓는다. 부모면 자식의 프로세서 id를 받는다.자식이면 0 부모는 
    
    int status;
    if(pid){
        //0보다 큰 int값이 나온다.음수는 실패!
        //wait(&status); //뒤진자식 상태 불러오기 블로킹 방식 
        while(!waitpid(pid, &status, WNOHANG)){
            printf("아직 자식이 살아있다.!\n");
            usleep(500000);
        }
        printf("Parents Process is done!\n");
    }else{
        
        for(int i=0; i<7; i++)
        {
            printf("Child Process number %d\n", i+1);
            sleep(1);           

        }
        printf("Childe Process is done!\n ");
    }



    return 0;
}