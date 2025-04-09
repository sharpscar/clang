#include<stdio.h>
#include<stdlib.h>
#define size 10

int main()
{
    // system("mode con:cols=90 lines=50");
    int map[size][size] = {0};
    int me[2] = {size - 1, size - 1}; // 9 9 내현재 좌표
    char input;

    while (input != 'q')
    {
        system("clear");
        for (int i = 0; i < size; i++)
        {
                for(int j = 0; j < size; j++)
                {
                    if((me[0] == i) && (me[1] == j)) // 내위치를 로 표시
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf(" ");  // 나머지는 
                    }
                }
                printf("\n");
        }

        scanf("%c", &input);
        if((input == 'w') && (me[0] > 0))   // w를 입력받고 내 y좌표(반복문에서 i)가 0보다 클때
        {
            me[0]--;
        }
        else if((input == 's') && (me[0] < 9))  // s를 입력받고 내 y좌표(반복문에서 i)가 9보다 클때
        {
            me[0]++;
        }
        else if((input == 'a') && (me[1] > 0))  // a를 입력받고 내 x좌표(반복문에서 j)가 0보다 클때
        {
            me[1]--;
        }
        else if((input == 'd') && (me[1] < 9))  // d를 입력받고 내 x좌표(반복문에서 j)가 9보다 클때
        {
            me[1]++;
        }

    }



    return 0;
}