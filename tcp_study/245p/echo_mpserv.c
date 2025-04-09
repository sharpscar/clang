#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define _XOPEN_SOURCE 200 
#include <signal.h>
//https://minusi.tistory.com/entry/struct-sigaction-%EB%B6%88%EC%99%84%EC%A0%84%ED%95%9C-%ED%98%95%EC%8B%9D-%EC%97%90%EB%9F%ACincomplete-type-error

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
   
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD, &act, 0);


    serv_sock=socket(PF_INET, SOCK_STREAM,0);    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock, 5)==-1)
        error_handling("listen()error");

    while(1)
    {
        adr_sz=sizeof(clnt_adr);
        /*성공시 파일디스크립터 실패시 -1반환
        여기서 accept함수를 호출하여 만들어진 소켓의 파일 디스크립터를 
        fork()수를 호출하므로써 부모프로세스와 자식프로세스가 동시에 하나씩 갖게된다.        
        */

        clnt_sock=accept(serv_sock,
                        (struct sockaddr*)&clnt_adr,
                        &adr_sz);
        
        if(clnt_sock==-1)
            continue;
        else
            puts("new client connected...");
        /*자식 생성*/
        pid=fork();
        
        /*실패*/
        if(pid==-1)
        {
            close(clnt_sock);
            continue;
        }
        
         /** 자식 실행영역
          *이부분에 의해서 클라에게 에코서비스가 제공됨 그런데 아래에서 서버소캣을 닫고있다. 이는 
          자식프로세스로 서버소켓의 파일디스크립터까지 복사되기 때문이다.
          * 
          */
        if(pid==0)
        {
            close(serv_sock); //왜 서버소캣을 닫냐?
            
            /** 파일 끝을 만나면 0을 뱉는 read함수 성공시 수신한 바이트수를 뱉는다. */
            while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0)
                write(clnt_sock, buf, str_len);
            
            close(clnt_sock);
            puts("client disconnected...");
            return 0;


        }
        else 
            close(clnt_sock);

    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;

    pid=waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d \n", pid);
}
void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

