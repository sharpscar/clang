#include <stdio.h>
#include <string.h>
#define TSIZE 45
#define FMAX 5
/* films1.c 구조체 배열을 사용한다.*/

struct film{
    char title[TSIZE];
    int rating;
};

char * s_gets(char * st, int n);
int main(void)
{
    struct film movies[FMAX];
    int i=0;
    int j;
    puts("첫번째 영화 타이틀을 입력하시오:");
    
    /**1. i는 5보다 작아야하고  2. 입력받는 영화제목이 이게 널이아니어야 하고 3. 널값이 아니었을때 */
    while(i<FMAX && s_gets(movies[i].title, TSIZE) != NULL&& movies[i].title[0] != '\0')
    {
        puts("평가를 입력하시오(0점에서 10점까지):");
        scanf("%d", &movies[i++].rating);
        
        while(getchar() !='\n')
            continue;
        puts("다음 영화 타이틀을 입력하시오(끝내려면 빈 라인):");
    }
    if(i==0)
    {
        printf("입력된 데이터가 없습니다.\n");        
    }
    else{
        printf("영화들의 목록은 다음과 같습니다.\n");
    }
    for(j=0; j<i;j++)
    {
        printf("영화:%s 평가 : %d\n", movies[j].title, movies[j].rating);
    }
    printf("끝\n");

    return 0;
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    /**
    fgets() 함수는 현재 stream 위치에서 어느 것이 먼저 오건 첫 번째 줄 바꾸기 문자(\n)까지, 
    스트림의 끝까지 또는 읽은 문자 수가 n-1과 같을 때까지 문자를 읽습니다. 
    fgets() 함수는 결과를 string에 저장하고 스트링 끝에 널(null) 문자(\0)를 추가합니다. 
    string은 줄 바꾸기 문자를 포함합니다(읽은 경우). n이 1이면 string이 비어 있습니다.   
     */
    ret_val = fgets(st, n, stdin);
    if(ret_val)
    {
        //https://blockdmask.tistory.com/389 strchr 문자열에서 문자를 찾는 함수
        find = strchr(st, '\n');
        if(find)
            *find = '\0';
        else
            while(getchar() !='\n')
                continue;
    }
    return ret_val;
}