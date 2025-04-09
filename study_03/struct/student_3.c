#include <stdio.h>

struct student{
    int kor, eng, math, tot;
    double avg;

};

int main()
{
    struct student stu[3]; // 구조체 student 의 변수 stu[]선언
    
    for(int i=0; i<3; ++i)
    {
        printf("[  student %d ]입력 \n", i+1);

        printf("국어 : ");
        scanf("%d", &stu[i].kor);

        
        printf("영어 : ");
        scanf("%d", &stu[i].eng);

        
        printf("수학 : ");
        scanf("%d", &stu[i].math);

        stu[i].tot = stu[i].kor + stu[i].eng + stu[i].math;
        stu[i].avg = stu[i].tot /3.;
    }
    printf("\n");

    for(int i=0; i<3; ++i){
        printf("student[%d] 총점 : %d\n", i+1, stu[i].tot);
        printf("student[%d] 평균 : %.2lf\n\n", i+1, stu[i].avg);
    }
    return 0;
}
