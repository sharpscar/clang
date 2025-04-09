#include <stdio.h>
#define LEN 20

const char * msgs[5] =
{
    "훌륭한 저녁 대접에 감사드립니다.",
    "당신의 직업이 ",
    "라는 점은 당신이 정말 특별한 분이라는 것을 증명합니다.",
    "우리는 맛있는 ",
    "를 먹고 약간 웃는 것 이상으로 함께했음에 틀림이 없습니다."
};

struct names{
    char first[LEN];
    char last[LEN];
};

struct guy{
    struct names handle;
    char favfood[LEN];
    char job[LEN];
    float income;
};

int main(void)
{
    struct guy fellow = {
        {"Ewen", "Villard"},
        "훈제 연어",
        "성격 코치",
        68112.00
    };

    printf("친애하는 %s \n\n", fellow.handle.first );
    printf("%s%s.\n",msgs[0], fellow.handle.first );
    printf("%s%s\n", msgs[1], fellow.job);
    printf("%s\n", msgs[2]);
    printf("%s%s%s", msgs[3], fellow.favfood, msgs[4]);
    if(fellow.income > 150000.0)
        puts("!!");
    else if(fellow.income >75000.0)
        puts("!");
    else
        puts(".");
    printf("\n%40s%s\n", " ", "또 뵈어요,");
    printf("%40s%s\n", "", "Shalala");

    return 0;
}