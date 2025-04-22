#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>

#define TSIZE 45
struct book
{
        int no;                     // No
        char title[SIZE];            // 제목
        char author[SIZE];            // 저자
        char publisher[SIZE];              // 출판사
        int pub_year;              //출판년
        int num_books;            //권
        char isbn[SIZE];                 //ISBN
        char extra_n[SIZE];              //부가기호
        char kdc[SIZE];                //KDC
        char kdc_subject[SIZE];        //KDC 주제명
        int loan_frequency;  
};

/*포괄적인 데이터형 정의*/
typedef struct book Item;

typedef struct node
{
    Item item;
    struct node * next;
}Node;

typedef Node * List;

/*함수 프로토 타입*/

/*
연산 리스트를 초기화한다.
사전조건 : plist는 리스트를 가리킨다
사후조건 : 리스트가 빈 상태로 초기화된다.
*/
void InitializeList(List * plist);


/*
연산 : 리스트가 비어 있는지 확인한다.
사전조건 : plist는 초기화된 리스트를 가리킨다
사후조건 : 리스트가 비어있으면 true를 리턴 else false를 리턴
*/
bool ListIsEmpty(const List *plist);

/*
연산 : 리스트가 가득 차있는지 확인한다.
사전조건 : plist는 초기화된 리스트를 가리킨다
사후조건 : 리스트가 가득 차있으면 true를 리턴한다. else false를 리턴
*/
bool ListIsFull(const List *plist);


/*
연산 : 리스트에 얼마나 많은 항목들이 있는지 확인한다.
사전조건 : plist는 초기화된 리스트를 가리킨다
사후조건 : 리스트에 있는 항목들의 개수를 리턴한다.
*/
unsigned int ListItemCount(const List *plist);


/*
연산 : 항목을 리스트의 끝에 추가한다.
사전조건 : item은 리스트에 추가할 항목이다.
        plist는 초기화된 리스트를 가리킨다
사후조건 : 가능할 경우 항목을 리스트 끝에 추가하고
        true를 리턴한다. else false를 리턴
*/
bool AddItem(Item item, List * plist);



/*
연산 : 리스트에 있는 각 항목에 함수를 적용한다.
사전조건 : plist는 초기화된 리스트를 가리킨다
        pfunc은 Item을 전달인자로 사용하고 리턴값이 없는 함수를 가리킨다.
사후조건 : pfun이 가리키는 함수는 리스트에 있는 각항목마다
        한번씩 수행된다.
*/
void Traverse(const List *plist, void(*pfun)(Item item));



/*
연산 : 가능할 경우에, 할당된 메모리를 해제한다.
사전조건 : plist는 초기화된 리스트를 가리킨다
         
사후조건 : 리스트에 할당된 모든 메모리가 해제되고
        리스트가 비어있는 상태로 설정된다.
*/
void EmptyTheList(List * plist);


#endif