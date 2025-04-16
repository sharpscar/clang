#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 45

struct film{
    char title[TSIZE];
    int rating;
    struct film* next; /* 리스트에 있는 다음 구조체를 가리킨다.*/
};

char* s_gets(char * st, int n);

int main(void)
{
    struct film * head = NULL;              // 최초의 구조체 위치를 저장한 포인터
    struct film * prev, * current, * rear; // [앞으로] [현재] [뒤로] 셋다 film구조체의 포인터
    char input[TSIZE];

    /* 영화 정보를 입력 받아 저장한다.*/
    puts("첫번째 영화 테이틀을 입력하시오:");

    while (s_gets(input, TSIZE) !=NULL && input[0] != '\0')
    {
        current =(struct film*) malloc(sizeof(struct film));
        if(head==NULL)
            head = current;
        else 
            prev->next = current; 
        
        
        
        current->next = NULL;
        strcpy(current->title, input);
        puts("평가를 입력하시오(0점에서 10점까지): ");
        scanf("%d", &current->rating);
        while(getchar()!='\n')
            continue;
        puts("다음 영화 타이틀을 입력하시오(끝내려면 빈라인): ");
        prev = current;
    }

    /*영화들의 목록을 보여준다.*/
    if(head==NULL)
        printf("입력된 데이터가 없습니다.\n");
    else
        printf("영화드르이 목록은 다음과 같습니다.");
    current = head;
    while(current != NULL)
    {
        printf("영화 %s 평가: %d\n", current->title, current->rating);
        current = current->next;
    }
    /*프로그램이 종료할때 할당된 메모리를 해제*/
    current = head;
    while(current !=NULL)
    {
        free(current);
        current = current->next;
    }
    printf("끝\n");
    return 0;
    
}

char * s_gets(char *st, int n)
{
    char * ret_val;
    char * find;

    ret_val =fgets(st, n, stdin);
    
    if(ret_val)
    {
        find = strchr(st, '\n');
        if(find)
            *find ='\0';
        else
            while(getchar() !='\n')
                continue;
    }
    return ret_val;
}