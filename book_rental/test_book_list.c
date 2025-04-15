#include <stdio.h>
#include <stdlib.h>
#include "cjson/cJSON.h"

#include <string.h>

char *read_json_file(const char *filename);

typedef struct book {
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


int main()
{

    

    
    char *json_string = read_json_file("books.json");
    if(!json_string){
        return 1;
    }   
    cJSON * json_array = cJSON_Parse(json_string);
    if(!json_array ||!cJSON_IsArray(json_array)){
        printf("JSON 파싱 실패 또는 배열이 아님\n");
        free(json_string);
        return 1;
    }

    int array_size = cJSON_GetArraySize(json_array);
    struct book books[array_size];
    memset(&books,0,sizeof(books));
    
    for(int i=0; i<array_size;i++)
    {
        cJSON *book = cJSON_GetArrayItem(json_array, i);
        if(!cJSON_IsObject(book)) continue;

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

    //    strcpy(books[i].name , name);
    //    printf("%s\n",name->valuestring);
        strcpy(books[i].isbn, isbn->valuestring);
        
        strcpy(books[i].name, name->valuestring);
        strcpy(books[i].publisher, publisher->valuestring);
        strcpy(books[i].writer, writer->valuestring);
        books[i].year = year->valueint;
        printf("%d년도 \n",books[i].year);
        
        books[i].count_book = count_book->valueint;
        printf("%d권수 \n",books[i].count_book);

        strcpy(books[i].add_sign, add_sign->valuestring);
        printf("%s추가기호 \n",books[i].add_sign);
        strcpy(books[i].kdc, kdc->valuestring);
        printf("%skdc \n",books[i].kdc);
        strcpy(books[i].topic, topic->valuestring);
        printf("%s토픽 \n",books[i].topic);
        
        
        books[i].frequency_rental= frequency_rental->valueint;
        printf("%d",frequency_rental->valueint);

        
        
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