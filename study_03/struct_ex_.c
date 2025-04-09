#include <stdio.h>

struct types {
    char ch;
    int i;
    float f; 
};

void func_1(struct types t) {
    t.ch = 'b';
    t.i = 20;
    t.f = 1.618;
}

struct types func_2(struct types t) {
    t.ch = 'c';
    t.i = 30;
    t.f = 1.414;
    return t;
}

void func_3(struct types* ptr) {
    ptr->ch = 'd';
    ptr->i = 40;
    ptr->f = 2.718;
}


int main() {
    struct types t;
    struct types* t_ptr = &t;

    t.ch = 'a';
    t.i = 10;
    t.f = 3.141;

    // printf("%c %d %f\n", t.ch, t.i, t.f);
    // printf("%p %p %p\n", &t.ch, &t.i, &t.f);

    // printf("%c %d %f\n", t_ptr->ch, t_ptr->i, t_ptr->f);
    // printf("%p %p %p\n", &(t_ptr->ch), &(t_ptr->i), &(t_ptr->f));

    // func_1(t);
    // printf("%c %d %f\n", t.ch, t.i, t.f);
    // printf("%p %p %p\n", &t.ch, &t.i, &t.f);

    t = func_2(t);
    printf("%c %d %f\n", t.ch, t.i, t.f);
    printf("%p %p %p\n", &t.ch, &t.i, &t.f);

    // func_3(t_ptr);
    // printf("%c %d %f\n", t.ch, t.i, t.f);
    // printf("%p %p %p\n", &t.ch, &t.i, &t.f);

    return 0;
}