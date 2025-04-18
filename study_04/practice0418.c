#include  <stdio.h>
struct film
{
    char title[TSIZE];
    int rating;
};

typedef struct film Item;

typedef struct node{
    Item item;
    struct node *next;
}Node;

int main()
{
    return 0;
}

bool AddItem(Item item, List * plist)
{
    Node *pnew;
    Node *scan = *plist;

    pnew = (Node *) malloc(sizeof(Node));
    /*메모리할당에 실패한상황*/
    if(pnew == NULL)
        return false;
    
    CopyToNode(item, pnew);
    pnew->next = NULL;
    /** 리스트가 비어있으면 pnew를 리스트의 머리에 넣는다.  
     * 함수 첫부분에 scan 에 리스트 포인터를 넘겨줬다. */
    if(scan==NULL)
        *plist = pnew;
    else
    {
        while(scan->next !=NULL)
            scan = scan->next;
        scan->next = pnew;

    }
    return true;

}

static void CopyToNode(Item item, Node *pnode)
{
    pnode->item = item;
}