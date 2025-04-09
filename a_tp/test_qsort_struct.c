#include <stdio.h>
#include <string.h> // to use strcmp
#include <stdlib.h> // to use qsort

typedef struct 
{
    char name[10];
    int age;
}Student_t;

int compfunc(const void *a, const void *b);
int main(void)
{
    int arr_count=5;
    Student_t student[5] ={
        {"bb",15},
        {"ab",11},
        {"aa",12},
        {"ba",19},
        {"ca",13}

    };

    printf("Before sorting the array\n");

    for( int i =0; i<arr_count; i++)
    {
        printf("%s %d\n", student[i].name, student[i].age);
    }
    printf("\n");

    //magic here
    qsort((Student_t*)student,arr_count,sizeof(Student_t),compfunc);

    printf("After sorting the array\n");

    for(int i=0; i<arr_count; i++)
    {
        printf("%s %d\n", student[i].name, student[i].age);
    }
    return 0;
}

int compfunc(const void *a, const void *b)
{
    return strcmp(((char*)a)->name, ((char*)b)->name);
}