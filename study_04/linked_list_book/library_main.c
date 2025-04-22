#include <stdio.h>
#include "library.h"

int main() {
    Book* library = NULL;  // 빈 도서관으로 시작

    // 도서 추가
    addBook(&library, "해리 포터와 마법사의 돌", "J.K. 롤링", "9788983920989");
    addBook(&library, "어린 왕자", "생텍쥐페리", "9788932917245");
    addBook(&library, "1984", "조지 오웰", "9788937460777");

    // 전체 도서 목록 출력
    printLibrary(library);

    // 도서 대출
    borrowBook(library, "9788983920989");  // 해리 포터 대출
    borrowBook(library, "9788983920989");  // 이미 대출된 도서 재대출 시도

    // 도서 반납
    returnBook(library, "9788983920989");  // 해리 포터 반납

    // 도서 삭제
    removeBook(&library, "9788932917245");  // 어린 왕자 삭제

    // 최종 도서 목록 출력
    printLibrary(library);

    // 메모리 해제
    freeLibrary(&library);
    return 0;
} 