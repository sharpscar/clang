#include <stdio.h>
#include <string.h>
#include <assert.h>
#define STR_SIZE 20

/**키보드 6.3만원
 * http://itempage3.auction.co.kr/DetailView.aspx?itemno=E851506355
 * https://sweetnew.tistory.com/235
 */


typedef struct book
{
    char name[STR_SIZE];
    char phone[STR_SIZE];
    int ringtone;
}PhoneBook;  //구조체 struct book 을 phoneBook이란 변수로 선언!

/**
 * 김밥 0, 라면1, 덮밥2, 찌개3, 떡볶이 4, 튀김 5, 기타 6, 음료 7
 * 
 */
typedef struct menu
{
    int category;  //0,1,2,3,4,5,6,7,8,9 
    char name[100];    
    int price;
}KimChoen;

int main()
{

    //구조체 배열등장!
    PhoneBook pb[]=     
    {
        {"홍길동","010-1111-1111",1},
        {"장보고","010-2222-2222",2},
        {"김유신","010-3333-3333",3},
        {"이순신","010-4444-4444",4},
        {"유관순","010-5555-5555",5},
        
    };

    
    KimChoen menus[]=
    {
        {0,"김밥",3000},
        {0,"치즈김밥",3500},
        {0,"참치김밥",3500},
        {0,"김치김밥",3500},
        {0,"야채김밥",3000},
        {0,"소고기김밥",4000},
        {0,"돈까스김밥",4000},
        {0,"삼겹살김밥",4500},

        {1,"라면",3000},
        {1,"계란라면",3500},
        {1,"치즈라면",3500},
        {1,"만두라면",3500},
        {1,"짬뽕라면",4000},
        {1,"떡라면",3500},
        {1,"떡만두라면",4000},

        {2,"제육덮밥",7000},
        {2,"오징어덮밥",7500},
        {2,"오징어제육덮밥",8000},
        {2,"돈까스덮밥",8000},
        {2,"쇠고기덮밥",8000},
        {2,"김치덮밥",7000},
        {2,"김치제육덮밥",7500},
        {2,"소시지덮밥",7500},
        {2,"오므라이스",7500},
        
        {3,"김치찌개",7000},
        {3,"오징어덮밥",7500},
        {3,"오징어제육덮밥",8000},
        {3,"돈까스덮밥",8000},
        {3,"쇠고기덮밥",8000},
        {3,"김치덮밥",7000},
        {3,"김치제육덮밥",7500},
        {3,"소시지덮밥",7500},
        {3,"오므라이스",7500},
        
        
    };


    //구조체의 포인터 변수 p를 생성한다. 현재 아무 주소도 
    //가리키고 있지 않다.
    PhoneBook *p = NULL;
    /*구조체 변수 pb[]에 대한 index 개수를 구한다. 5?*/
    int size = sizeof(pb)/ sizeof(pb[0]);
    // assert(size != 5);
    
    //입력받을 이름을 저장할 변수
    char name[STR_SIZE];

    printf("검색할 이름을 입력하세요!! \n");
    printf("이름 :");
    scanf("%s", name);


    /* pb 배열을 사이즈만큼반복하여 찾음 ! 
     name 과 pb[i].name과 같으면 구조체의 포인터 변수 *p에 해당하는
     pb[] index의 주소값을 저장!
    */
    for (int i=0; i<size; ++i)
    {
        if(strcmp(name, pb[i].name)==0)
        {
            p = &pb[i]; //해당 pb의 주소를 포인터 변수에 넣음!  해당하는게 있으면 어떤 액션을 취한다.! or 없으면 없다 출력!
            break;
        }
    }

    if(p == NULL)
    {
        printf("입력한 이름의 정보가 없엉!");
    }else{
        printf("%s의 연락처 :%s\n", p->name, p->phone);
    }


    return 0;
}