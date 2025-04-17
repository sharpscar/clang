/*list.c 리스트를 연산 대상으로 하는 지원 함수들*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* 지역 함수 프로토 타입*/
static void CopyToNode(Item item, Node *pnode);

/*인터페이스 함수
리스트를 빈 상태로 초기화 한다.
*/
void InitailizeList(List* plist){
    *plist = NULL;
}

/*리스트가 비어 있으면 true를 리턴한다.*/
bool ListIsEmpty(const List *plist)
{
    if(*plist == NULL)
        return true;
    else
        return false;
}

/* 리스트가 가득 차 있으면 true를 리턴한다.*/
bool ListIsFull(const List *plist)
{
    Node * pt;
    bool full;
    pt = (Node *) malloc(sizeof(Node));
    if(pt==NULL)
        full=true;
    else 
        full=false;
    free(pt);
}