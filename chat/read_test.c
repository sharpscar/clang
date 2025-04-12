#include <stdio.h>
#include <stdlib.h>


typedef struct Config{
    char ip[20];
    char port[10];
    char nick[100];
}network_config;

int config_read(network_config* config, char* path);

int main(int argc, char argvs[])
{
    
    char *path ="./config.conf";
    network_config myconf;    
    config_read(&myconf, path);

    // 태ㅔ스트
    printf("test ip : %s\n",myconf.ip);
    printf("test port : %s\n",myconf.port);
    printf("test nick : %s\n",myconf.nick);


    
    return 0;
}


int config_read(network_config* config, char* path)
{

    FILE* in = NULL;  
    in =  fopen(path, "r");
    char* ptr[256];
    char* str[128];
    // 파일이 안열린다.
    if(in ==0){
        printf("파일을 열 수 없습니다.");
        return 0;
    }else{
        
        const int max = 100;
        char line[max], ip[20], port_[20], nic_name[50];
        
    
        // printf("허허?");
        fgets(line,max,in);
        sscanf(line, "%s %s %s", ip, port_,nic_name);
        // printf("%s\n", line);
        
        strcpy(config->ip, ip);
        
        strcpy(config->port, port_);
        
        strcpy(config->nick, nic_name);          
    }

}
