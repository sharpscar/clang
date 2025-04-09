#include <stdio.h>

struct types
{
    char ch;
    int i;
    float f;
};



int main ()
{
    struct types t;
    struct types* t_pointer = &t;

    t.ch = 'a';
    t.i = 10;
    t.f = 3.141;

    printf("%c %d %f\n", t.ch, t.i, t.f);
    printf("%p %p %p\n", &t.ch, &t.i, &t.f); //4바이트 잡은이유 - 변할수있다.중요한건 붙어있다.


    my_func(t_pointer);
    // func_1(t);

    printf("===========================================================");
    printf("값복사와 리턴 하는거");
    t = func_2(t);
    
    printf("%c %d %f\n", t.ch, t.i, t.f);
    printf("%p %p %p\n", &t.ch, &t.i, &t.f);

}

void my_func(struct types* a )
{
    printf("%c %d %f\n", a->ch, a->i, a->f);
    printf("%p %p %p\n", &(a->ch), &(a->i), &(a->f)); //4바이트 잡은이유 - 변할수있다.중요한건 붙어있다.


}

void func_1(struct types t)
{
    t.ch ='b';
    t.i = 20;
    t.f = 1.618; //황금비


}


struct types func_2(struct types t)
{
    t.ch ='c';
    t.i = 30;
    t.f = 1.414; //황금비
    return t;
}

void func_3(struct types* ptr)
{
    ptr->ch = 'd';
    ptr->i =40;
    ptr->f = 2.718;
}

