#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char * argv[])
{
    int serv_sock, clnt_sock;
    FILE* readfp;
    FILE* writefp;

    /**sockaddr_in의 등장배경!
     * sa_data에 저장되는 주소정보에는 ip주소와 port번호가 포함되어야하고
     * 이 두가지 정보를 담고 남은 부분은 0으로 채울것을 bind함수는 요구한다.
     
     */
    struct sockaddr_in serv_adr, clnt_adr;

    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE]= {0,};
    serv_sock=socket(PF_INET, SOCK_STREAM,0);
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    bind(serv_sock,
        (struct sockaddr*)&serv_adr, 
        sizeof(serv_adr)
    );

    listen(serv_sock, 5);
    clnt_adr_sz=sizeof(clnt_adr);
    /**listen함수호출 이후에 클라이언트의 연결요청이 들어왔다면 
     * 들어온 순서대로 연결요청을 수락해야한다. 데이터를 주고 받으려면
     * 소켓이 있어야한다 이미 소켓이 있지만 서버소켓은 문지기 역할이고
     * accept함수 호출 결과로 클라이언트 소캣과 자동으로 연결된다.
     */
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    readfp=fdopen(clnt_sock, "r");
    writefp=fdopen(clnt_sock,"w");
    fputs("FROM SERVER: Hi~ client? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awsome! \n", writefp);
    fflush(writefp);

    fclose(writefp);
    fgets(buf, sizeof(buf), readfp);
    fputs(buf, stdout);
    fclose(readfp);
    return 0;
}
