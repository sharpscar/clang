#include <stdio.h>

struct Check{
    int id;
    int age;
    char name[30];
};

int main()
{
    struct Check p1 = {1,19, "김철수"};
    int * ptr = 0x10101000000;
    printf("%p", ptr);
    // wrong(ptr);
    return 0;
}