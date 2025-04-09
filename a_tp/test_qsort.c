#include <stdio.h>
#include <stdlib.h> //qsort를 사용하려면 써야됨!

//compare function prototype
int cmpfunc(const void *a, const void *b);

int main(void)
{
    int arr_count=5;
    int arr[5] = {5,3,1,4,2};

    printf("Before sort the array\n");

    for( int i=0; i<arr_count; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");

    // magic here!
    qsort((int*)arr, arr_count, sizeof(int), cmpfunc);

    printf("After sort the array\n");
    for( int i=0; i<arr_count; i++)
    {
        printf("%d", arr[i]);
    }
    return 0;
}


int cmpfunc(const void *a, const void *b)
{
    return (*(char*)a - *(char*) b);
}