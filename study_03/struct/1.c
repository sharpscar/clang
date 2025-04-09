#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include <string.h>

struct student{
    int id;
    char name[20];
    int score;
};

int main()
{
    struct student stu1;
    struct student stu2;
    struct student stu3;

    stu3.id = 4567;
    strcpy(stu3.name, "ccc"); //구조체의  name 속성에 "ccc" 문자열
    stu3.score =90;

    printf("[ stu3 ]\n");
    printf("id : %d\n", stu3.id);
    printf("name : %s\n", stu3.name);
    printf("score : %d\n", stu3.score);

      //구조체변수 stu1에 stu2값을 저장한다.
      // 구조체 멤버 변수의 자료형이 같아도 구조체가 다르면 복사되지 않는다.
    stu1 = stu2;

    if(stu1.id == stu2.id && strcmp(stu1.name, stu2.name) == 0 && stu1.score == stu2.score)
        printf("\nstu1 and stu1 are equal.\n");

    return 0;
}


/**
 * 구조체 객체 복사
 */