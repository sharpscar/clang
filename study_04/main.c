#include <stdio.h>
#include "linked_list.h"

int main() {
    Node* head = NULL;  // 빈 리스트로 시작

    // 리스트에 노드 추가
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtBeginning(&head, 5);
    insertAtEnd(&head, 30);

    // 리스트 출력
    printf("초기 리스트: ");
    printList(head);

    // 노드 삭제
    deleteNode(&head, 20);
    printf("20을 삭제한 후: ");
    printList(head);

    // 메모리 해제
    freeList(&head);
    return 0;
} 