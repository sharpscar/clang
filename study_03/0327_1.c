#include <stdio.h>

a=0;

void global()
{
    printf("전역 a=%d\n", a);

    for( int a=4 ; a<4; a++)
    {
        printf("4. 지역 내부의 지역안의 for문 a= %d\n", a);
    }
}

void reg()
{
    register int a = -1;
}
void st()
{
    static int a = 4;
    printf("5. 지연 안의 함수 호출 속의 static a = %d\n",a );
}


int main()
{

    printf("1. 전역a = %d\n", a);

    a=1;

    printf("2. 지역 내부의 a=%d\n", a);
    
    for(int a=3; a<4; a++)
    {
        printf("3. 지역 내부의 지역안의 for문의 a= %d\n",a);
    }

    printf("6. 지역 내부의 a= %d\n",a);




    global();

    st();

    printf("함수 실행 이후의 지역 내부의 a=%d\n", a);
    return 0;
}