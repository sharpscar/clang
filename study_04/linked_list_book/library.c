#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

Book* createBook(const char* title, const char* author, const char* isbn) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    
    strncpy(newBook->title, title, 99);
    strncpy(newBook->author, author, 49);
    strncpy(newBook->isbn, isbn, 19);
    newBook->title[99] = '\0';
    newBook->author[49] = '\0';
    newBook->isbn[19] = '\0';
    newBook->is_borrowed = false;
    newBook->next = NULL;
    
    return newBook;
}

void addBook(Book** library, const char* title, const char* author, const char* isbn) {
    Book* newBook = createBook(title, author, isbn);
    
    if (*library == NULL) {
        *library = newBook;
        return;
    }
    
    // ISBN 중복 체크
    if (findBook(*library, isbn) != NULL) {
        printf("이미 존재하는 ISBN입니다: %s\n", isbn);
        free(newBook);
        return;
    }
    
    // 리스트의 끝에 추가
    Book* current = *library;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newBook;
}

void removeBook(Book** library, const char* isbn) {
    Book* current = *library;
    Book* prev = NULL;
    
    while (current != NULL && strcmp(current->isbn, isbn) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("해당 ISBN을 가진 책을 찾을 수 없습니다: %s\n", isbn);
        return;
    }
    
    if (prev == NULL) {
        *library = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("책이 성공적으로 삭제되었습니다 (ISBN: %s)\n", isbn);
}

void borrowBook(Book* library, const char* isbn) {
    Book* book = findBook(library, isbn);
    if (book == NULL) {
        printf("해당 ISBN을 가진 책을 찾을 수 없습니다: %s\n", isbn);
        return;
    }
    
    if (book->is_borrowed) {
        printf("이미 대출 중인 도서입니다.\n");
        return;
    }
    
    book->is_borrowed = true;
    printf("'%s' 도서가 대출되었습니다.\n", book->title);
}

void returnBook(Book* library, const char* isbn) {
    Book* book = findBook(library, isbn);
    if (book == NULL) {
        printf("해당 ISBN을 가진 책을 찾을 수 없습니다: %s\n", isbn);
        return;
    }
    
    if (!book->is_borrowed) {
        printf("이미 반납된 도서입니다.\n");
        return;
    }
    
    book->is_borrowed = false;
    printf("'%s' 도서가 반납되었습니다.\n", book->title);
}

void printLibrary(Book* library) {
    if (library == NULL) {
        printf("도서관이 비어있습니다.\n");
        return;
    }
    
    printf("\n도서 목록:\n");
    printf("----------------------------------------\n");
    Book* current = library;
    while (current != NULL) {
        printf("제목: %s\n", current->title);
        printf("저자: %s\n", current->author);
        printf("ISBN: %s\n", current->isbn);
        printf("상태: %s\n", current->is_borrowed ? "대출 중" : "대출 가능");
        printf("----------------------------------------\n");
        current = current->next;
    }
}

void freeLibrary(Book** library) {
    Book* current = *library;
    while (current != NULL) {
        Book* next = current->next;
        free(current);
        current = next;
    }
    *library = NULL;
}

Book* findBook(Book* library, const char* isbn) {
    Book* current = library;
    while (current != NULL) {
        if (strcmp(current->isbn, isbn) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
} 