#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// 노드 구조체 정의
typedef struct Node {
    int data;              // 데이터 저장
    struct Node* next;     // 다음 노드를 가리키는 포인터
} Node;

// 연결 리스트 함수 선언
Node* createNode(int data);
void insertAtBeginning(Node** head, int data);
void insertAtEnd(Node** head, int data);
void deleteNode(Node** head, int data);
void printList(Node* head);
void freeList(Node** head);

#endif 