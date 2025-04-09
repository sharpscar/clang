#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

enum {KIMBOB,RAMEN,DUPBOB,JJIGAE,DDUKBOK,TWIGIM,DRINKS,GUITAR};


#define STR_SIZE 50

/**키보드 6.3만원
 * http://itempage3.auction.co.kr/DetailView.aspx?itemno=E851506355
 * https://sweetnew.tistory.com/235
 * 
 * https://dojang.io/mod/page/view.php?id=571
 * 
 */

 
 int get_input_1();
/**
 * 김밥 0, 라면1, 덮밥2, 찌개3, 떡볶이 4, 튀김 5, 기타 6, 음료 7
 * 
 */
struct menu
{
    int category;  //0,1,2,3,4,5,6,7,8,9 
    char name[100];    
    int price;
};

struct receip
{
    int total;
    char discount[100]; // 디스카운트 내역
    int discount_;
};


struct order
{
    // int order_; //주문 순서까지 넣어주는 친절함!!
    int category;
    char name[100];
    int price;
    int quentity;
    int total;
};


int get_input_1()
{
    int answer_1;
    printf("메뉴명 기준 몇개 주문하시겠습니까 \n");
    scanf("%d", &answer_1);


    
    return answer_1;
}

int get_input_3()
{
    int is_package;
    //포장인지 매장인지 //    
    printf("포장하실건가요? 포장은 1, 매장은 2) ");
    scanf("%d", &is_package);
    return is_package;
}
int get_input_4()
{
    //현금인지 카드인지
    int is_cash;
    //포장인지 매장인지 //    
    
    printf("카드결제인가요 ? 카드결제는 1, 현금결제는 2) "); 
    scanf("%d", &is_cash);
    return is_cash;
}


void show_menus(struct menu *menus, int cnt)
{
 
    for(int i=0; i<cnt ; i++)
    {
        printf("메뉴 %d)%s\t\t",i+1,menus[i].name);
    }
}

// 메뉴판 , 메뉴판의 메뉴 갯수,  주문숫자
struct orders *get_input_2(struct menu *menus, int len,int cnt)
{
    char menu_name[100];
    int quentity;
  
    struct order o;
    // struct order os[100]; //메뉴를 하번에 몇개 주문할지모르니까 일단 100개
    struct order *os = malloc(sizeof(struct order));
    //메뉴들 검색하는 함수호출 - quentity만큼 반복 해당하는게 있으면 메뉴를 담자
    for(int i=0; i<cnt; i++)
    {
        
        // int menu_size = 48;//  sizeof(menus)/ sizeof(menus[0]);
        printf("메뉴명은 어떻게 되십니까? \n");
        scanf("%s", menu_name);
        printf("수량은 몇개를 주문하시겠습니까? \n");
        scanf("%d", &quentity);
        //메뉴명은 문자열이라 포인터인 매개변수로 넘김
        // len = 48개의 메뉴에서 찾는다.
        for(int j=0; j<len; j++)
        {
            if(strcmp(menu_name, menus[j].name)==0)
            {
                o.category = menus[j].category;
                strcpy(o.name, menus[j].name);
                o.price = menus[j].price;
                o.quentity= quentity;
                os[i]= o;        
            }
        }        
    }
    // free(os);
    return os;
}


struct recicp*  calcuate_discount(struct order *order_ptr,int how_many_menu,int is_package,int is_cash)
{
   
    int kate_0=0, kate_1=0,kate_2=0,kate_3=0,kate_4=0,kate_5=0,kate_6=0,kate_7=0;
    int sp_temp=0, kimra_temp=0, dduk_temp=0,discount=0, total_money=0, total_count = 0;
    for(int i=0; i<how_many_menu; i++)
    {   
        switch (order_ptr[i].category)
        {
        case 0:
            kate_0 +=order_ptr[i].quentity;
            break;
        case 1:
            kate_1 +=order_ptr[i].quentity;
            break;
        case 2:
            kate_2 +=order_ptr[i].quentity;
            break;
        case 3:
            kate_3 +=order_ptr[i].quentity;
            break;
        case 4:
            kate_4 +=order_ptr[i].quentity;
            break;
        case 5:
            kate_5 +=order_ptr[i].quentity;
            break;
        case 6:
            kate_6 +=order_ptr[i].quentity;
            break;
        case 7:
            kate_7 +=order_ptr[i].quentity;
            break;        

        default:
            break;
        }
        // 카테고리를 기준으로 메뉴의 갯수를 가져온다.  김라셋,   떡튀셋, 스페셜셋 크게 이렇게 나뉜다.

        order_ptr[i].total = order_ptr[i].quentity* order_ptr[i].price;
        total_money =total_money + order_ptr[i].total;
        total_count += order_ptr[i].quentity;
    }

    if (((kate_0 > 0)&& (kate_1 > 0))&&((kate_4 > 0)&& (kate_5 > 0)))
    {
        while(((kate_0 > 0)&& (kate_1 > 0))&&((kate_4 > 0)&& (kate_5 >0)))
        {
            kate_0--;
            kate_1--;
            kate_4--;
            kate_5--;
            sp_temp++;
        }
    }

    if ((kate_0 > 0)&& (kate_1 > 0))
    {
        while((kate_0 > 0)&& (kate_1 > 0))
        {
            kate_0--;
            kate_1--;            
            kimra_temp++;
        }
    }

    if ((kate_4 > 0)&& (kate_5 > 0))
    {
        while((kate_4 > 0)&& (kate_5 > 0))
        {
            kate_4--;
            kate_5--;            
            dduk_temp++;
        }
    }

    struct receip r;
    struct receip *pr;  // 영수증 구조체를 리턴해보자!
    pr = &r;

   
    // printf("총 비용은 %d 할인금액은 %d 입니다.\n", total_money,discount);   
    if(is_package==1)
    {   
        printf("-포장비용 2000원 추가입니다.\n");
        // char s1[500] = "[포장]\n"; 
        total_money = total_money +2000;
    }       
    if(is_cash ==1)
    {
        printf("-현금결제입니다..\n");
        // char s3[50] = "[카드]\n";        
        
    }
    if(total_count >=5)
    {
        printf("-메뉴 5개이상 음료무료 \n");
        // char s4[50]= "[음료무료]\n";
    }
    if(total_count >=10)
    {
        printf("-메뉴 10개이상 음료무료 \n");
        // char s5[50]="메뉴10개이상 10%%할인";
        total_money = total_money - (total_money *10) /100;
    }
    
    // char s1[50] = "";
      

    if(sp_temp >=1)
    {

        discount += sp_temp *2000;
        
        // strcat(s1,s2);
        pr = (&(struct receip){.discount ="-스페셜세트", .total=total_money-discount, .discount_ = discount});
        // myorder = (&(struct order){.category=menus[i].category, .name=menus[i].name, .price =menus[i].price, .quentity=quentity});            
        return pr;

    }
    else if(dduk_temp >=1)
    {
        // char s2[50] = "-떡튀세트";
        discount += dduk_temp *1000;
        
        pr = (&(struct receip){.discount ="-떡튀세트", .total=total_money-discount, .discount_ = discount});
        return pr;
        
    } else if(kimra_temp >=1)
    {
        // char s2[50] = "-떡튀세트";
        discount += kimra_temp *500;
        
        pr = (&(struct receip){.discount ="-김라세트", .total=total_money-discount, .discount_ = discount});
        return pr;
    } 
    //적용되는 세트가 없다.
    pr = (&(struct receip){.discount ="-세트적용 없음", .total=total_money-discount, .discount_ = discount});

    return pr;
}

/*
할인정보 계산 함수를 테스트하는 코드
order배열과 주문메뉴갯수를 매개변수로 넣으면 할인계산하여 할인액을 리턴하는 함수
만약 함수가 잘 동작하면 함수에는 문제가 없는것
*/
void case1_call_calcuate_discount_()
{
    // 김밥 2개 라면1개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order orders[2];
    struct order *os = malloc(sizeof(struct order));

    struct order m1, m2;

    m1.category = KIMBOB;
    strcpy(m1.name ,"김밥");
    m1.price = 3000;
    m1.quentity = 2;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    os[0] = m1;

    m2.category = RAMEN;
    strcpy(m2.name ,"라면");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    os[1] = m2;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &os;
    int discount = calcuate_discount(myorder,2,1,1);
    // assert(500==discount);

    printf("계산된 할인액은 ?%d\n", discount);

}
void case3_call_calcuate_discount_()
{
    // 김밥 1개참치김밥1 라면2개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order *os = malloc(sizeof(struct order));
    struct order orders[100];
    struct order m1, m2,m3;

    m1.category = KIMBOB;
    strcpy(m1.name ,"김밥");
    m1.price = 3000;
    m1.quentity = 1;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    orders[0] = m1;

    m2.category = KIMBOB;
    strcpy(m2.name ,"참치김밥");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[1] = m2;

    m3.category = RAMEN;
    strcpy(m3.name ,"라면");
    m3.price = 3000;
    m3.quentity = 2;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[2] = m3;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &orders;
    int discount = calcuate_discount(myorder,3,1,2);
    // assert(discount==1000);

    printf("계산된 할인액은 ?%d\n", discount);

    
}

void case4_call_calcuate_discount_()
{
    // 김밥 1개참치김밥1 라면2개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order *os = malloc(sizeof(struct order));
    struct order orders[100];
    struct order m1, m2,m3;

    m1.category = KIMBOB;
    strcpy(m1.name ,"참치김밥");
    m1.price = 3000;
    m1.quentity = 1;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    orders[0] = m1;

    m2.category = RAMEN;
    strcpy(m2.name ,"짬뽕라면");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[1] = m2;

    // m3.category = RAMEN;
    // strcpy(m3.name ,"라면");
    // m3.price = 3000;
    // m3.quentity = 2;
    // // m2.total = m2.price * m2.quentity; //여기까지가 라면
    // orders[2] = m3;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &orders;
    int discount = calcuate_discount(myorder,2,2,1);
    // assert(discount==500);
    //
    printf("계산된 할인액은 ?%d\n", discount);

    
}

void case5_call_calcuate_discount_()
{
    // 김밥 1개참치김밥1 라면2개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order *os = malloc(sizeof(struct order));
    struct order orders[100];
    struct order m1, m2,m3;

    m1.category = TWIGIM;
    strcpy(m1.name ,"고추튀김");
    m1.price = 3000;
    m1.quentity = 1;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    orders[0] = m1;

    m2.category = DDUKBOK;
    strcpy(m2.name ,"떡볶이");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[1] = m2;

    // m3.category = RAMEN;
    // strcpy(m3.name ,"라면");
    // m3.price = 3000;
    // m3.quentity = 2;
    // // m2.total = m2.price * m2.quentity; //여기까지가 라면
    // orders[2] = m3;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &orders;
    int discount = calcuate_discount(myorder,2,2,2);
    // assert(discount==500);
    //
    printf("계산된 할인액은 ?%d\n", discount);

    
}
void case6_call_calcuate_discount_()
{
    // 김밥 1개참치김밥1 라면2개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order *os = malloc(sizeof(struct order));
    struct order orders[100];
    struct order m1, m2,m3;

    m1.category = TWIGIM;
    strcpy(m1.name ,"김말이튀김");
    m1.price = 3000;
    m1.quentity = 2;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    orders[0] = m1;

    m2.category = DDUKBOK;
    strcpy(m2.name ,"떡볶이");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[1] = m2;

    // m3.category = RAMEN;
    // strcpy(m3.name ,"라면");
    // m3.price = 3000;
    // m3.quentity = 2;
    // // m2.total = m2.price * m2.quentity; //여기까지가 라면
    // orders[2] = m3;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &orders;
    int discount = calcuate_discount(myorder,2,2,1);
    // assert(discount==500);
    //
    printf("계산된 할인액은 ?%d\n", discount);

    
}

void case7_call_calcuate_discount_()
{
    // 스페셜세트4개를 orders 주문에 넣어서 테스팅을 해본다.
    // struct order *os = malloc(sizeof(struct order));
    struct order orders[100];
    struct order m1, m2,m3,m4;

    m1.category = TWIGIM;
    strcpy(m1.name ,"김말이튀김");
    m1.price = 3000;
    m1.quentity = 1;
    // m1.total = m1.price * m1.quentity; //여기까지가 김밥
    orders[0] = m1;

    m2.category = DDUKBOK;
    strcpy(m2.name ,"떡볶이");
    m2.price = 3000;
    m2.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[1] = m2;

    m3.category = KIMBOB;
    strcpy(m3.name ,"김밥");
    m3.price = 3000;
    m3.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[2] = m3;

    m4.category = RAMEN;
    strcpy(m4.name ,"라면");
    m4.price = 3000;
    m4.quentity = 1;
    // m2.total = m2.price * m2.quentity; //여기까지가 라면
    orders[3] = m4;

    // m3.category = RAMEN;
    // strcpy(m3.name ,"라면");
    // m3.price = 3000;
    // m3.quentity = 2;
    // // m2.total = m2.price * m2.quentity; //여기까지가 라면
    // orders[2] = m3;

    // 생성한 오더배열을 calcuate_discount함수에 전달하면 어떻게 반응하는지 테스트 가능하다.
    struct order *myorder;
    myorder = &orders;
    int discount = calcuate_discount(myorder,4,2,2);
    // assert(discount==500);
    //
    printf("계산된 할인액은 ?%d\n", discount);

    
}



int main()
{

    struct menu menus[]=
    {
        {KIMBOB,"김밥",3000},
        {KIMBOB,"치즈김밥",3500},
        {KIMBOB,"참치김밥",3500},
        {KIMBOB,"김치김밥",3500},
        {KIMBOB,"야채김밥",3000},
        {KIMBOB,"소고기김밥",4000},
        {KIMBOB,"돈까스김밥",4000},
        {KIMBOB,"삼겹살김밥",4500},

        {RAMEN,"라면",3000},
        {RAMEN,"계란라면",3500},
        {RAMEN,"치즈라면",3500},
        {RAMEN,"만두라면",3500},
        {RAMEN,"짬뽕라면",4000},
        {RAMEN,"떡라면",3500},
        {RAMEN,"떡만두라면",4000},

        {DUPBOB,"제육덮밥",7000},
        {DUPBOB,"오징어덮밥",7500},
        {DUPBOB,"오징어제육덮밥",8000},
        {DUPBOB,"돈까스덮밥",8000},
        {DUPBOB,"쇠고기덮밥",8000},
        {DUPBOB,"김치덮밥",7000},
        {DUPBOB,"김치제육덮밥",7500},
        {DUPBOB,"소시지덮밥",7500},
        {DUPBOB,"오므라이스",7500},
        
        {JJIGAE,"김치찌개",7000},
        {JJIGAE,"된장찌개",7000},
        {JJIGAE,"참치김치찌개",7500},
        {JJIGAE,"고기듬뿍 김치찌개",8000},
        {JJIGAE,"차돌된장찌개",8000},
        {JJIGAE,"부대찌개",8000},
        {JJIGAE,"동태찌개",8000},
        {JJIGAE,"순두부찌개",8000},
        
        {DDUKBOK,"떡볶이",5000},
        {DDUKBOK,"치즈떡볶이",6000},
        {DDUKBOK,"해물떡볶이",7000},
        {DDUKBOK,"짜장떡볶이",7000},
        {DDUKBOK,"라볶이",6000},
        {DDUKBOK,"치즈라볶이",7000},

        {TWIGIM,"김말이튀김",4000},
        {TWIGIM,"야채튀김",4000},
        {TWIGIM,"만두튀김",4000},
        {TWIGIM,"고추튀김",5000},
        {TWIGIM,"오징어튀김",5000},

        {GUITAR,"공기밥",1000},

        {DRINKS,"콜라",1000},
        {DRINKS,"사이다",1000},
        {DRINKS,"오렌지환타",1000},
        {DRINKS,"파인애플환타",1000},
        
    };

    // 구조체 포인터를 이용해 메뉴를 출력한다.
    show_menus(menus, 48);
  
    printf("\n");
    printf("\n");

    int is_cash, is_package;
    is_package = get_input_3(); // 1은 포장 2는 매장

    is_cash = get_input_4();  // 1은 카드 2는 현금

    int how_many_menu;
    //사용자 입력을 받는 곳
    how_many_menu= get_input_1();
    //여기에 포장? 매장? 질문하여 변수에 넣자
    
    int discount;
     // 구조체로 만든 메뉴정보들을 포인터 변수로 만듬
    struct menu *menu_ptr;  
    struct order *kimbab_order;
    menu_ptr = &menus;    
    
    kimbab_order = get_input_2(menu_ptr, 48, how_many_menu);    
    
    struct receip r;
    struct receip* pr;
    pr = &r;
    pr = calcuate_discount(kimbab_order, how_many_menu,  is_package, is_cash);


    

    printf("할인적용된 내용은 %s\n",pr->discount);
    printf("할인액은 %d원 입니다.\n", pr->discount_);
    printf("총 비용은 %d원 입니다.\n", pr->total);

     
   
    

}
   
    
    
   


  