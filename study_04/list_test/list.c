#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//지역함수 프로토타입
static void CopyToNode(Item item, Node * pnode);

//인터페이스 함수 리스트를 빈상태로 초기화한다.
void InitializeList(List * plist)
{
    *plist = NULL;
}

//리스트가 비어있으면 ture를 리턴
bool ListIsEmpty(const List * plist)
{
    if(*plist==NULL)
        return true;
    else
        return false;
}

// 리스트가 가득 차 있으면 true를 리턴한다.
bool ListIsFull(const List * plist)
{
    Node * pt;
    bool full;

    pt = (Node* )malloc(sizeof(Node));
    if(pt ==NULL)
        full = true;
    else 
        full= false;
    free(pt);

    return full;
}


//노드의 개수를 리턴
unsigned int ListItemCount(const List * plist)
{
    unsigned int count = 0;
    Node * pnode = *plist; // 리스트의 시작으로 설정한다.

    while(pnode != NULL)
    {
        ++count;
        pnode = pnode->next;  // 다음 노드로 설정한다.
    }
    return count;
}

//항목을 저장할 노드를 생성하고, plist가 가리키는 리스트의 끝에 그것을 추가한다.
bool AddItem(Item item, List * plist)
{
    Node * pnew;
    Node * scan = *plist;
    pnew = (Node*) malloc(sizeof(Node));
    if(pnew==NULL)
        return false; //실패했을때 함수 탈출!
    
    CopyToNode(item,pnew);
    pnew->next = NULL;
    if(scan ==NULL)
        *plist = pnew;
    else
    {
        while(scan->next != NULL)
            scan = scan->next;
        scan->next = pnew;
    }
    return true;
}

// 각 노드에 접근하여 pfun이 가리키는 함수를 적용한다.
void Traverse(const List * plist, void(*pfun)(Item item))
{
    Node * pnode = *plist;          // 리스트의 시작으로 설정한다.
    while(pnode != NULL)
    {
        (*pfun)(pnode->item);        //항목에 함수를 적용한다.
        pnode = pnode->next;         //다음 항목으로 진행한다.
    }
}

/*
malloc()에 의해서 할당된 메모리를 해제한다.
리스트 포인터를 NULL로 설정한다.
*/
void EmptyTheList(List * plist)
{
    Node * psave;

    while(*plist !=NULL)
    {
        psave = (*plist)->next;
        free(*plist);
        *plist = psave;
    }
}

static void CopyToNode(Item item, Node* pnode)
{
    pnode -> item =item;        //  구조체를 복사한다.
}