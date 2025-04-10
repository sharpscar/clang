#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thread_main(void* arg){
    int cnt = *((int*)arg);
    for(int i=0; i<cnt; i++){
        sleep(1);
        printf("Thread Running\n");
    }
    printf("Inner Thread Off\n");
}

int main(){
    pthread_t t_id;
    int param = 5;

    if(pthread_create(&t_id, NULL,thread_main, &param )!=0){
        return -1;
    }
    sleep(3);
    printf("MainThread Off\n");
    return 0;
}