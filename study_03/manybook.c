#include <assert.h>
#include <stdio.h>
#include <string.h>

char * s_gets(char * st, int n);
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

struct book{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

int main(void)
{
    struct book library[MAXBKS];
    int count =0;
    int index;

    printf("도서 제목을 입력하시오.\n");
    printf("끝내려면 라인의 시작 위치에서 [enter]키를 누르시오.\n");
    while( count<MAXBKS && s_gets(library[count].title, MAXTITL) !=NULL&& library[count].title[0]!='\0')
    {
        printf("저자명을 입력하시오.\n");
        s_gets(library[count].author, MAXAUTL);
        printf("정가를 입력하시오.\n");
        scanf("%f", &library[count++].value);
        while(getchar() !='\n')
            continue;
        if(count <MAXBKS)
            printf("다음 타이틀을 입력하시오.\n");
    }
    if(count >0)
    {
        printf("다음은 소장하고 있는 도서들의 목록입니다.:\n");
        for(index=0; index <count; index++)
        {
            printf("%s by%s: $%.2f\n", library[index].title, library[index].author, library[index].value);
        }
    }
    else{
        printf("책이 한권도 없어요? 아, 장하다 장해.\n");
        }          
    return 0;
    
}
char * s_gets(char * st, int n)
    {
        char * ret_val;
        char * find;

        ret_val = fgets(st, n, stdin);
        printf("%d\n", ret_val);
        // assert(ret_val == typeof(char));
        if(ret_val)
        {
            find = strchr(st, '\n');
            if(find)
                *find ='\0';
            else 
                while (getchar() != '\n')
                    continue;
        }
        return ret_val;
    }