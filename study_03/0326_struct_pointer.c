#include <stdio.h>

struct student{
    int grade;
    int num;
    char name[10];

};

int main()
{
    struct student people;
    struct student *person;

    person = &people; //people변수의 주소값을 person포인터에 넘긴다.
    (*person).grade =10;

    printf("참조연산자 %d\n", (*person).grade);
    printf("간접참조연산자 %d\n", person->grade);
}