#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>

// 책 정보를 담는 구조체
typedef struct Book {
    char title[100];
    char author[50];
    char isbn[20];
    bool is_borrowed;
    struct Book* next;
} Book;

// 도서관 함수들
Book* createBook(const char* title, const char* author, const char* isbn);
void addBook(Book** library, const char* title, const char* author, const char* isbn);
void removeBook(Book** library, const char* isbn);
void borrowBook(Book* library, const char* isbn);
void returnBook(Book* library, const char* isbn);
void printLibrary(Book* library);
void freeLibrary(Book** library);
Book* findBook(Book* library, const char* isbn);

#endif 