#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

int main(int argc, char * argv[])
{
    pid_t pid = fork();

    if(pid==0)
    {
        puts("Hi, I am a child process");
    }
    else
    {
        printf("Child process ID: %d \n", pid);
        sleep(30); //sleep 30 sec
    }

    if(pid==0)
        puts("end child process");
    else
        puts("End parent process");
    return 0;
}