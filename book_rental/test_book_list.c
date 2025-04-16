#include <stdio.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#define BOOK_SIZE 10000
#include <string.h>

/**
 * NULL 0  없음 구분해라 
 * 매개변수에 포인터 넣을때 배열은 기본 포인터인데 &로 넣으면 포인터의 포인터주소가 가버리는문제가
 *
 */

typedef struct {
    int no;
    char isbn[50];
    char name[50];
    char writer[50] ;
    char publisher[200] ;
    int year ;
    int count_book;
    char add_sign[50] ;
    char kdc[50] ;
    char topic[50] ;
    int frequency_rental ;
}books;

void store_to_struct(books *b );
char *read_json_file(const char *filename);

int main()
{
    

    // int book_size = 10000;  배열선언은 무조건 상수로 싫으면 malloc
    books b[BOOK_SIZE];

    // memset(b,0,sizeof(books));
    // printf("허허");
    store_to_struct(b);
    
}

void store_to_struct(books *b)
{
    printf("허허");
    char *json_string = read_json_file("books.json");
    if(!json_string){
        printf("jsonfile 읽다가 문제생김");
    }   

    cJSON * json_array = cJSON_Parse(json_string);
    if(!json_array ||!cJSON_IsArray(json_array)){
        printf("JSON 파싱 실패 또는 배열이 아님\n");
        
        exit(1);
    }
    
    int array_size = cJSON_GetArraySize(json_array);  
    
    // memset(b,0,sizeof(books)*book_size);
    
    for(int i=0; i<array_size;i++)
    {
        cJSON *book = cJSON_GetArrayItem(json_array, i);
        if(!cJSON_IsObject(book)) continue;

        cJSON *no = cJSON_GetObjectItemCaseSensitive(book,"No");
        cJSON *isbn = cJSON_GetObjectItemCaseSensitive(book,"ISBN");
        cJSON *name = cJSON_GetObjectItemCaseSensitive(book, "제목");
        cJSON *writer = cJSON_GetObjectItemCaseSensitive(book, "저자");
        cJSON *publisher = cJSON_GetObjectItemCaseSensitive(book, "출판사");
        cJSON *year = cJSON_GetObjectItemCaseSensitive(book, "출판년");
        cJSON *count_book = cJSON_GetObjectItemCaseSensitive(book, "권");
        
        cJSON *add_sign = cJSON_GetObjectItemCaseSensitive(book,"부가기호");
        cJSON *kdc = cJSON_GetObjectItemCaseSensitive(book,"KDC");
        cJSON *topic = cJSON_GetObjectItemCaseSensitive(book,"KDC 주제명");
        cJSON *frequency_rental = cJSON_GetObjectItemCaseSensitive(book,"대출 빈도");

        b[i].no = no->valueint;
        // printf("허허");
        strcpy(b[i].name , name->valuestring);
        printf("%s\n",name->valuestring);
        strcpy(b[i].isbn, isbn->valuestring);
        
        strcpy(b[i].name, name->valuestring);
        strcpy(b[i].publisher, publisher->valuestring);
        strcpy(b[i].writer, writer->valuestring);
        b[i].year = year->valueint;
        printf("%d년도 \n",b[i].year);
        
        b[i].count_book = count_book->valueint;
        printf("%d권수 \n",b[i].count_book);

        strcpy(b[i].add_sign, add_sign->valuestring);
        printf("%s추가기호 \n",b[i].add_sign);
        strcpy(b[i].kdc, kdc->valuestring);
        printf("%skdc \n",b[i].kdc);
        strcpy(b[i].topic, topic->valuestring);
        printf("%s토픽 \n",b[i].topic);
        
        b[i].frequency_rental= frequency_rental->valueint;
        

        // printf("%d. ",i+1);
        // printf("name %s\n", b[i].name);
        // printf("isbn %s\n", b[i].isbn);
        // printf("제목: %s\n", name->valuestring);
        // printf("저자: %s\n", writer->valuestring);
        
        
    }
}

char *read_json_file(const char *filename){
    FILE * file = fopen(filename, "r");
    if(!file){
        printf("파일을 열수 없습니다. %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_data = (char *)malloc(file_size+1);
    if(!json_data){
        printf("메모리 할당 실패\n");
        fclose(file);
        return NULL;
    }

    fread(json_data, 1,file_size, file);
    json_data[file_size] = '\0';

    fclose(file);
    return json_data;
}