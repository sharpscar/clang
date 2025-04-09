#include <stdio.h>

#define MAX_SPEED 200 //최고속도
#define STEP 2 //연료 소모량
#define FULL 10 // 증감 속도량

struct car{
    char name[20];
    int speed;
    int gas;

};

typedef struct car Car; //모든 함수에서 사용하기 위해 전역변수로 만든다?

void carStatus(Car*); //자동차의 현재상태를 출력하는 함수
void carAccel(Car*); //악셀 패달을 밟는 동작을 구현하는 함수
void carBreak(Car*); //브레이크 패달을 밟는 동작을 구현하는 함수


int main()
{
    Car c = {
        "my_car",0,100
    };

    printf("초기화된 차 정보\n");
    /*
    구조체에 저장된 정보를 출력하는 함수를 정의하기 위해 
    구조체의 주소값을 전달한다.
    */
    carStatus(&c); 
    printf("악셀을 밟은 후의 차 정보\n");
    carAccel(&c);

    printf("악셀을 밟은 후의 차정보\n");
    carAccel(&c);
    carStatus(&c);
    return 0;
}

void carStatus(Car* c)
{
    // c.name => c->name
    printf("자동차명 : %s\n", c->name);
    //구조체의 포인터는 ->로 표시한다!
    printf("현재속도 : %d km/s\n", c->speed);
    //'%'는 서식문자에 사용되고있다. 따라서 그 기능을 무효화 해주기 위해 %%를 입력해준다.
    printf("현재연료 : %d %%\n\n", c->gas);
}

void carAccel(Car* c)
{
    //악셀을 밟아 speed를 증가시키는 함수다. 그리고 동시에 gas를소모
    if(c->gas >= STEP)
    {
        //gas가 연료소모량 STEP(2) 보다 크거나 같다면,
        c->gas -= STEP;
        // speed 값이 MAX_SPEED(200)을 초과했는지 확인한다.
        if(c->speed + FULL > MAX_SPEED)
            c->speed = MAX_SPEED;
        else 
            c->speed += FULL;
    }
    else 
        printf("연료가 부족합니다.\n");
}

void carBreak(Car* c)
{
    if(c->speed < FULL)
        c->speed = 0;
    else 
        c->speed -= FULL;
}
