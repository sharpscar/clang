#include <stdio.h>
#include <string.h>

enum genre{KPOP, POP, CLASSIC, OST};
enum choice { ADD=1, PRINT, SEARCH, DELETE};

typedef struct music{
    char title[20];
    char artist[20];
    int genre;
}MUSIC;

int CNT= 0;
MUSIC mlist[100] = {0,};

void menu();

//  레코드를 추가하는 함수!
MUSIC add_record();
void print_record(MUSIC* list, int cnt); // 음반을 출력 (구조체 배열, 배열의 크기)
void search_record(MUSIC* list, int cnt);
void delete_record(MUSIC* list, int cnt);

int main(void)
{
    int choice; 

    menu();
    while(1)
    {
        
        printf("\n메뉴 입력: ");
        scanf_s("%d", &choice);
        if(choice ==5)break;
        getchar();

        switch(choice)
        {
            case ADD:
                mlist[CNT]= add_record();
        }
    }

}

