#include <stdio.h>


typedef struct student
{
    int number;
    char name[50];
}Students;

typedef struct book
{
    char name[50];
    char phone[50];
    int ringtone;
}PhoneBook;  //구조체 struct book 을 phoneBook이란 변수로 선언!

/**
 * 
 * 함수에 정적으로 넘겨주자
 * 
typedef struct book
{
    char name[STR_SIZE];
    char phone[STR_SIZE];
    int ringtone;
}PhoneBook;  //구조체 struct book 을 phoneBook이란 변수로 선언!

 * 
 * 
 */

 void my_function(Students *std, int size_)
 {
    for(int i=0; i<size_; i++)
    {
        printf("%s\n", std[i].name);
    }
 }


int main()
{

    Students std[] = {
        {1,"야스오"},
        {2,"피들스틱"},
        {3,"피즈"},
        {4,"샤코"},
        {5,"사이온"},
        {6,"티모"},
        {7,"제드"},
        {8,"럭스"}

    };

    my_function(std,sizeof(std)/sizeof(Students));
    // int arr_1d[9] = {1,2,3,4,5,6,7,8,9};
    
    // int arr_2d[3][3] = {
    //     {1,2,3},
    //     {4,5,6},
    //     {7,8,9}

    // };

    // arr_show(&arr_2d);

    


    return 0;
}
