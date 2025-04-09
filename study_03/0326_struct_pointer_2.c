#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int num1 =20;

    int* numPtr1;
    long long *numPtr3 = malloc(sizeof(long long));

    numPtr1 =&num1;

    memset(numPtr3, 0x27, 8); //numPtr3가 가리키는 메모리를 8byte만큼 0x27로 설정
    int * numPtr2;

    numPtr2 = malloc(sizeof(int));

    printf("%p\n", numPtr1);
    printf("%p\n", numPtr2);
    printf("0x%llx\n",*numPtr3);

    free(numPtr2);
    free(numPtr3);
    return 0;
}