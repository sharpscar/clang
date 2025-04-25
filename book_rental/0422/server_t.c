#include <stdio.h>              // 표준 입출력 함수 사용 (printf, fopen 등)
#include <stdlib.h>             // 동적 메모리 할당 (malloc, free 등)
#include <string.h>             // 문자열 처리 함수 (strcmp, strcpy 등)
#include <unistd.h>             // POSIX API (read, write, close 등)
#include <pthread.h>            // 쓰레드 사용을 위한 헤더
#include <netinet/in.h>         // 소켓 주소 구조체를 위한 헤더 (struct sockaddr_in 등)
#pragma pack(1)
#include "cJSON.h"   // JSON 처리 라이브러리 헤더
#include "cJSON.c"
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX_BOOKS 11000           // 도서 최대 등록 수
#define MAX_USERS 500
#define PORT 2222             // 서버가 열릴 포트 번호
#define SIZE 100

// 도서 구조체 정의
typedef struct {
    int no;                     // No
    char title[SIZE];            // 제목
    char author[SIZE];            // 저자
    char publisher[SIZE];              // 출판사
    int pub_year;              //출판년
    int num_books;            //권
    char isbn[SIZE];                 //ISBN
    char extra_n[SIZE];              //부가기호
    char kdc[SIZE];                //KDC
    char kdc_subject[SIZE];        //KDC 주제명
    int loan_frequency;      //대출 빈도
} Book;

typedef struct {
    char id[50];
    char pw[50];
    char name[50];
    int age;
    char phone[50];
    char addr[50];
    int msc;
} User;

typedef struct {

    char date[100];
    char day_[50];
    int is_open;  // 1이면 영업 0이면 휴일
}bussiness_month;


// 전역 도서 배열과 관련 변수 선언
Book books[MAX_BOOKS];          // 도서 목록을 저장할 배열
User Users[MAX_USERS];
int book_count = 0;             // 현재 등록된 도서 수
int user_count = 0; // 현재 등록된 유저 수
pthread_mutex_t book_mutex = PTHREAD_MUTEX_INITIALIZER;  // 도서 데이터 접근 동기화를 위한 뮤텍스

int search_user_by_id(char *user_id);
void set_calendar(bussiness_month *m, int mon);
void make_json_file_for_bussiness(bussiness_month *m, int mon);
void set_calendar(bussiness_month *m, int mon);
void solution(int a, int b, char *c);
int set_work_day(int month, int day, bussiness_month *m4);
int is_open_for_business(bussiness_month *m, int mon, int day);
int set_holiday(int mon, int day,bussiness_month *ms);
void parsing_json_to_struct_for_bussiness(bussiness_month *m, int mon);
char *read_json_file(const char *filename);

int set_work_day(int month, int day, bussiness_month *m4)
{

    // int a,b;
    // printf("업무일로 설정할 날짜정보를 입력하세요 예 4월 24일: 4 24       \n");
    // scanf("%d %d", &a, &b);

    char date_[50];
    sprintf(date_, "2025-%d-%d",month,day);
    int result =0;
    for(int i=0; i< 30; i++)
    {
        
        // printf("%s\n", m4[i].date);
        if(strcmp(m4[i].date, date_)==0)
        {
            // printf("%s %s\n",m4[i].date, date_);
            m4[i].is_open = 1;
            printf("%s를 업무일로 설정 완료!\n", m4[i].date);
            
            return 1;

        }else{
            result = 0;
        }

       
        
    }
    return result;
}

void parsing_json_to_struct_for_bussiness(bussiness_month *m, int mon)
{
    char *json_string = read_json_file("example_4.json");
    if(!json_string){
        printf("jsonfile 읽다가 문제생김");
    }
    cJSON * json_array = cJSON_Parse(json_string);
    
    if(!json_array ||!cJSON_IsArray(json_array)){
        printf("JSON 파싱 실패 또는 배열이아님\n");
        exit(1);
    }

    // int array_size = cJSON_GetArraySize(json_array);

    for(int i=0; i<31; i++)
    {
        

        cJSON *day = cJSON_GetArrayItem(json_array,i);
        if(!cJSON_IsObject(day)) continue;

        /*
        "date" : "2025-4-1",
        "day_" : "화",
        "is_open" : 1
        */
        cJSON *d1 = cJSON_GetObjectItemCaseSensitive(day,"date");
        cJSON *d2 = cJSON_GetObjectItemCaseSensitive(day,"day_");
        cJSON *d3 = cJSON_GetObjectItemCaseSensitive(day,"is_open");
        strcpy(m[i].date, d1->valuestring);
        strcpy(m[i].day_, d2->valuestring);
        m[i].is_open=d3->valueint;

        printf("함수 parsing_json_to_struct_for_bussiness %s\n", m[i].date);
    
        

    }

}


char *read_json_file(const char *filename)
{
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

int set_holiday(int mon, int day,bussiness_month *m)
{

 
    int result;
    char date_[50];
    sprintf(date_, "2025-%d-%d",mon,day);
    
    for(int i=1; i< 31; i++)
    {
        if(i!=0)
        {
            // printf("%s\n", m4[i].date);
            if(strcmp(m[i].date, date_)==0)
            {
                // printf("%s %s\n",m4[i].date, date_);
                m[i].is_open = 0;
                printf("%s를 휴일로 설정 완료!\n", m[i].date);
                
                return 1;
            }
            else {
                result =0;
            }

        }
        
        
    }
    return result;
}


int is_open_for_business(bussiness_month *m, int mon, int day)
{
    

    char date_[50];
    sprintf(date_, "2025-%d-%d",mon,day);

   
    for(int i=0; i< 31; i++)
    {
        
        // printf("%s\n", m4[i].date);
        if(strcmp(m[i].date, date_)==0)
        {
            
            if(m[i].is_open ==1)
            {
                return 1;
            }
            else{
                return 0;

            }
            

        }
    }
}

// 도서 목록을 JSON 파일에서 불러오는 함수
int load_books(const char *filename) {
    FILE *fp = fopen(filename, "r");      // 파일 열기
    if (!fp) return 0;                    // 파일이 없으면 0 리턴

    fseek(fp, 0, SEEK_END);               // 파일 끝으로 이동
    long len = ftell(fp);                // 파일 길이 측정
    rewind(fp);                           // 다시 파일 처음으로 이동

    char *data = malloc(len + 1);         // JSON 데이터 저장할 메모리 할당
    fread(data, 1, len, fp);              // 파일 데이터 읽기
    fclose(fp);                           // 파일 닫기
    data[len] = '\0';                    // 문자열 종료 문자

    cJSON *root = cJSON_Parse(data);      // JSON 파싱
    if (!root) return 0;                  // 파싱 실패 시 0 반환

    int count = 0;
    cJSON *book;
    cJSON_ArrayForEach(book, root) {      // JSON 배열 순회
        books[count].no = cJSON_GetObjectItem(book, "No")->valueint;
        strcpy(books[count].title, cJSON_GetObjectItem(book, "제목")->valuestring);  
        strcpy(books[count].author, cJSON_GetObjectItem(book, "저자")->valuestring);
        strcpy(books[count].publisher, cJSON_GetObjectItem(book, "출판사")->valuestring);
        books[count].pub_year = cJSON_GetObjectItem(book, "출판년")->valueint;
        books[count].num_books = cJSON_GetObjectItem(book, "권")->valueint;
        strcpy(books[count].isbn, cJSON_GetObjectItem(book, "ISBN")->valuestring);
        strcpy(books[count].extra_n, cJSON_GetObjectItem(book, "부가기호")->valuestring);
        strcpy(books[count].kdc, cJSON_GetObjectItem(book, "KDC")->valuestring);
        strcpy(books[count].kdc_subject, cJSON_GetObjectItem(book, "KDC 주제명")->valuestring);
        books[count].loan_frequency = cJSON_GetObjectItem(book, "대출 빈도")->valueint;
        
        count++;                                                                // 도서 수 증가
    }
    
    cJSON_Delete(root);            // JSON 객체 해제
    free(data);                    // 메모리 해제
    book_count = count;            // 총 도서 수 저장
    return count;                  // 로드된 도서 수 반환
}
int load_user(const char *filename) {
    FILE *fp = fopen(filename, "r");      // 파일 열기
    if (!fp) return 0;                    // 파일이 없으면 0 리턴

    fseek(fp, 0, SEEK_END);               // 파일 끝으로 이동
    long len = ftell(fp);                // 파일 길이 측정
    rewind(fp);                           // 다시 파일 처음으로 이동

    char *data = malloc(len + 1);         // JSON 데이터 저장할 메모리 할당
    fread(data, 1, len, fp);              // 파일 데이터 읽기
    fclose(fp);                           // 파일 닫기
    data[len] = '\0';                    // 문자열 종료 문자

    cJSON *root = cJSON_Parse(data);      // JSON 파싱
    if (!root) return 0;                  // 파싱 실패 시 0 반환

    int count_2 = 0;
    cJSON *User;
    cJSON_ArrayForEach(User, root) {      // JSON 배열 순회
        strcpy(Users[count_2].id, cJSON_GetObjectItem(User, "id")->valuestring);
        strcpy(Users[count_2].pw, cJSON_GetObjectItem(User, "password")->valuestring);  
        strcpy(Users[count_2].name, cJSON_GetObjectItem(User, "name")->valuestring);
        Users[count_2].age = cJSON_GetObjectItem(User, "age")->valueint;
        strcpy(Users[count_2].phone, cJSON_GetObjectItem(User, "phone")->valuestring);
        strcpy(Users[count_2].addr, cJSON_GetObjectItem(User, "addr")->valuestring);
        Users[count_2].msc = cJSON_GetObjectItem(User, "messagecount")->valueint;

        count_2++;                                                                // 도서 수 증가
    }
    
    cJSON_Delete(root);            // JSON 객체 해제
    free(data);                    // 메모리 해제
    user_count = count_2;            // 총 도서 수 저장
    return count_2;                  // 로드된 도서 수 반환
}


// 도서 목록을 JSON 파일로 저장하는 함수
int save_books(const char *filename) {
    cJSON *root = cJSON_CreateArray();     // 빈 JSON 배열 생성
    for (int i = 0; i < book_count; i++) {
        cJSON *b = cJSON_CreateObject();                                   // 각 도서를 위한 객체 생성
        cJSON_AddNumberToObject(b, "No", books[i].no);
        cJSON_AddStringToObject(b, "제목", books[i].title);            // 저자 추가
        cJSON_AddStringToObject(b, "저자", books[i].author);
        cJSON_AddStringToObject(b, "출판사", books[i].publisher);
        cJSON_AddNumberToObject(b, "출판년", books[i].pub_year);
        cJSON_AddNumberToObject(b, "권", books[i].num_books);
        cJSON_AddStringToObject(b, "ISBN", books[i].isbn);
        cJSON_AddStringToObject(b, "부가기호", books[i].extra_n);
        cJSON_AddStringToObject(b, "KDC", books[i].kdc);
        cJSON_AddStringToObject(b, "KDC 주제명", books[i].kdc_subject);
        cJSON_AddNumberToObject(b, "대출 빈도", books[i].loan_frequency);
        cJSON_AddItemToArray(root, b);                                    // 배열에 추가
    }
    char *out = cJSON_Print(root);                // JSON 문자열로 변환
    FILE *fp = fopen(filename, "w");              // 파일 쓰기 모드로 열기
    fputs(out, fp);                               // 파일에 저장
    fclose(fp);                                   // 파일 닫기
    free(out);                                    // 문자열 메모리 해제
    cJSON_Delete(root);                           // JSON 배열 해제
    return 1;
}
/**
 * pthread_mutex_lock(&book_mutex);          // 쓰레드 동기화를 위한 뮤텍스 잠금
    books[book_count++] = b;                  // 배열에 도서 추가
    save_books("DATA.json");             // 저장
    pthread_mutex_unlock(&book_mutex);
 */
// 유저 목록을 JSON 파일로 저장하는 함수


int save_user(const char *filename) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < user_count; i++) {
        


        cJSON *u = cJSON_CreateObject();                                   
        cJSON_AddStringToObject(u, "id", Users[i].id);
        cJSON_AddStringToObject(u, "password", Users[i].pw);           
        cJSON_AddStringToObject(u, "name", Users[i].name);
        cJSON_AddNumberToObject(u, "age", Users[i].age);
        cJSON_AddStringToObject(u, "phone", Users[i].phone);
        cJSON_AddStringToObject(u, "addr", Users[i].addr);
        cJSON_AddNumberToObject(u, "messagecount", Users[i].msc);
        cJSON_AddItemToArray(root, u);      
                                    // 배열에 추가
    }

    

    char *out = cJSON_Print(root);                // JSON 문자열로 변환
    FILE *fp = fopen(filename, "w");              // 파일 쓰기 모드로 열기
    fputs(out, fp);                               // 파일에 저장
    fclose(fp);                                   // 파일 닫기
    free(out);                                    // 문자열 메모리 해제
    cJSON_Delete(root);
                               // JSON 배열 해제
    return 1;
}


void make_json_file_for_bussiness(bussiness_month *m, int mon)
{
    int DayOfMonth[12] =  {31,28,31,30,31,30,31,31,30,31,30,31};
    char file_name[50];
    sprintf(file_name, "example_%d.json", mon);
    FILE *fp = fopen(file_name, "w");

    
    fprintf(fp, "[");
    
    for(int i=0; i<(DayOfMonth[mon-1]);i++) 
    {
        
        fprintf(fp,"{\n");
        fprintf(fp, "\"date\" : \"%s\",\n",m[i].date);
        fprintf(fp, "\"day_\" : \"%s\",\n",m[i].day_);
        fprintf(fp, "\"is_open\" : %d\n",m[i].is_open);

        printf("loooog  make_json_file      %d\n",i);
        if (i<29) //5월일땐 30으로 변경해야함
        {
            /* code */
            fprintf(fp, "},\n");
        }else{
            fprintf(fp, "}\n");
        }      
        
        
         
                     
    }

    fprintf(fp, "]\n"); //전체닫기
    fclose(fp);
}


void set_calendar(bussiness_month *m, int mon)
{

    // bussiness_month_4 m4[32];
    //달력 배열은 30개  날짜별로  날짜 , 요일, 영업유무를 담는다.

    //날짜와 요일을 만들고 영업유무에 값을 넣는 함수를 만든다. 
    char date_[50];
    char day_[10];
    int DayOfMonth[12] =  {31,28,31,30,31,30,31,31,30,31,30,31};

    for(int i=0; i<DayOfMonth[mon-1]+1; i++)
    {
        if(i!=0)
        {
            sprintf(date_ ,"2025-%d-%d",mon,i);
            // printf("%s  ",date_);
            strcpy(m[i].date, date_);
            solution(mon,i, day_);  //날짜를 넣어서 
            // printf("%s\n", day_);        
            strcpy(m[i].day_,day_);        


            /**set_calendar 함수에서의 내용 */
            printf("set_calendar    >%s\n",date_);

            if((strcmp(m[i].day_,"토")==0)||(strcmp(m[i].day_,"일")==0))
            {
                m[i].is_open = 0;
                // printf("휴일입니다.\n");
            }else{
                m[i].is_open = 1;
                // printf("영업일입니다.\n");
            }

        }
        
    }
    // for(int i=1; i<31; i++)
    // {
    //     printf("날짜: %s  ",m4[i].date);
    //     printf("%s 요일:",m4[i].day_);
    //     printf("영업 유무 %d \n",m4[i].is_open);
    // }

}


/** 4월달 요일을 뱉는 함수 */
void solution(int a, int b, char *c) {
    char *DayOfTheWeek[] = {"일","월","화","수","목", "금","토"};

    int DayOfMonth[12] =  {31,28,31,30,31,30,31,31,30,31,30,31};
    int Total = 0;
    // printf("%d\n", a);
   //    a--;
   char the_day[10];
   while(a>0){
    Total +=DayOfMonth[--a];
   }   
   Total += b;
   
   strcpy(c,DayOfTheWeek[Total%7] );

}


// 키워드로 도서 검색 후 갯수 반환
int search_books_count(const char *key, const char *value) {
    int found = 0;
    for (int i = 0; i < book_count; i++)
    {
        if ((strcmp(key, "title") == 0 && strstr(books[i].title, value)) || (strcmp(key, "author") == 0 && strstr(books[i].author, value))) 
        {
            found++;  // 검색 결과에 추가

        }
    }
    return found;  // 검색된 도서 수 반환
}
// 키워드로 도서 검색 후 반환
void search_books(const char *key, const char *value, Book *results) {
    int found = 0;
    for (int i = 0; i < book_count; i++)
    {
        if ((strcmp(key, "title") == 0 && strstr(books[i].title, value)) || (strcmp(key, "author") == 0 && strstr(books[i].author, value))) 
        {
            results[found++] = books[i];  // 검색 결과에 추가

        }
    }
}

int search_user_by_id(char *user_id)
{
    for(int i=0; i<user_count; i++)
    {
        if(strcmp(Users[i].id, user_id)==0)
        {
            return 1; // 찾으면 1 리턴
        }
    }
    return 0; //기본값은 못찾았는걸로
}


// 도서 추가
int add_book(Book b) {
    pthread_mutex_lock(&book_mutex);          // 쓰레드 동기화를 위한 뮤텍스 잠금
    books[book_count++] = b;                  // 배열에 도서 추가
    save_books("DATA.json");             // 저장
    pthread_mutex_unlock(&book_mutex);        // 뮤텍스 해제
    return 1;
}

// 도서 삭제
int delete_book(char *isbn) {
    pthread_mutex_lock(&book_mutex);
    int found = 0;
    for (int i = 0; i < book_count; i++)
    {
        if (strcmp(books[i].isbn, isbn) ==0)
        {
            for (int j = i; j < book_count - 1; j++) books[j] = books[j + 1];  // 뒤로 밀기
            book_count--;
            found = 1;
            break;
        }
    }
    if (found) save_books("DATA.json");
    pthread_mutex_unlock(&book_mutex);
    return found;
}

// 도서 수정
int modify_book(Book b) {
    pthread_mutex_lock(&book_mutex);
    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].isbn, b.isbn) == 0)
        {
            books[i] = b;
            save_books("DATA.json");
            pthread_mutex_unlock(&book_mutex);
            return 1;
        }
    }
    pthread_mutex_unlock(&book_mutex);
    return 0;
}
void create_user_folder(const char *id) {
    char path[256];

    // 기본 경로 + 사용자명으로 폴더 경로 구성
    snprintf(path, sizeof(path), "/home/yang/C/project11/%s", id);

    // 폴더 생성 (0755 권한)
    if (mkdir(path, 0755) == -1) {
        if (errno == EEXIST) {
            printf("이미 폴더가 존재합니다: %s\n", path);
        } else {
            perror("폴더 생성 실패");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("폴더가 생성되었습니다: %s\n", path);
    }
}
// 로그인 기능
int login(const char *id, const char *pw) {
    FILE *fp = fopen("users.json", "r");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    char *data = malloc(len + 1);
    fread(data, 1, len, fp);
    data[len] = '\0';
    fclose(fp);

    cJSON *root = cJSON_Parse(data);
    cJSON *user;
    cJSON_ArrayForEach(user, root) {
        char *uid = cJSON_GetObjectItem(user, "id")->valuestring;
        char *pwd = cJSON_GetObjectItem(user, "password")->valuestring;
        if (strcmp(uid, "admin") == 0 && strcmp(id, "admin") == 0 && strcmp(pwd, pw) == 0){
            free(data);
            cJSON_Delete(root);
            return 2;
        }
        if (strcmp(uid, "saseo") == 0 && strcmp(id, "saseo") == 0 && strcmp(pwd, pw) == 0){
            free(data);
            cJSON_Delete(root);
            return 3;
        }
        else if (strcmp(uid, id) == 0 && strcmp(pwd, pw) == 0) {
            free(data);
            cJSON_Delete(root);
            return 1; 
        }
    }
    free(data);
    cJSON_Delete(root);
    return 0;
}

// 회원가입 기능
int register_user(const char *id, const char *pw, const char *nickname, int year, const char *phone, const char *address, int messege_a) {
    FILE *fp = fopen("users.json", "r");
    cJSON *root = NULL;

    if (fp) {
        fseek(fp, 0, SEEK_END);
        long len = ftell(fp);
        rewind(fp);

        char *data = malloc(len + 1);
        fread(data, 1, len, fp);
        data[len] = '\0';
        fclose(fp);

        root = cJSON_Parse(data);
        free(data);
    }

    if (!root) {
        root = cJSON_CreateArray(); // 파일이 없거나 JSON 파싱 실패 시 새로 생성
    }

    // 중복 아이디 체크
    cJSON *user;
    cJSON_ArrayForEach(user, root) {
        char *uid = cJSON_GetObjectItem(user, "id")->valuestring;
        if (strcmp(uid, id) == 0) {
            cJSON_Delete(root);

            return 0; // 중복
        }
    }

    // 새 사용자 생성
    cJSON *new_user = cJSON_CreateObject();
    cJSON_AddStringToObject(new_user, "id", id);
    cJSON_AddStringToObject(new_user, "password", pw);
    cJSON_AddStringToObject(new_user, "name", nickname);
    cJSON_AddNumberToObject(new_user, "age", year);
    cJSON_AddStringToObject(new_user, "phone", phone);
    cJSON_AddStringToObject(new_user, "addr", address);
    cJSON_AddNumberToObject(new_user, "messagecount", messege_a);
    cJSON_AddItemToArray(root, new_user);

    // 파일에 저장
    fp = fopen("users.json", "w");
    if (!fp) {
        cJSON_Delete(root);
        return 0;
    }

    char *out = cJSON_Print(root);
    fputs(out, fp);
    fclose(fp);

    free(out);
    cJSON_Delete(root);
    create_user_folder(id);
    return 1;
}

// 클라이언트 요청을 처리하는 쓰레드 함수
void *client_handler(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);  // 할당된 메모리 해제
    char cmd[16], id[50], pw[50], nickname[50], phone[50], address[100];
    int year;
    int messege_a;

    /* 달력정보를 초기화하는 내용 */
    bussiness_month m4[31];
    memset(&m4, 0, sizeof(bussiness_month)*31);
    parsing_json_to_struct_for_bussiness(m4, 4);


    read(client_socket, cmd, sizeof(cmd));
    read(client_socket, id, sizeof(id));
    read(client_socket, pw, sizeof(pw));

    int result = 0;

    if (strcmp(cmd, "login") == 0) {
        result = login(id, pw);
    } else if (strcmp(cmd, "register") == 0) {
        // 추가 정보 읽기
        read(client_socket, nickname, sizeof(nickname));
        read(client_socket, &year, sizeof(int));
        read(client_socket, phone, sizeof(phone));
        read(client_socket, address, sizeof(address));
        read(client_socket, &messege_a, sizeof(int));

        result = register_user(id, pw, nickname, year, phone, address, messege_a);
    }

    // 결과 전송
    write(client_socket, &result, sizeof(int));


    if (result == 1 && strcmp(cmd, "login") == 0) {
        while (1) {
            char action[16];
            read(client_socket, action, sizeof(action));  // 사용자 요청
            action[strcspn(action, "\n")] = '\0';
            if (strcmp(action, "1") == 0)
            {
                char id_[50];
                read(client_socket, id, sizeof(id));
                strcpy(id_, id);
                
                FILE *fp = fopen("users.json", "r");
                if (!fp) return 0;
                fseek(fp, 0, SEEK_END);
                long len = ftell(fp);
                rewind(fp);

                char *data = malloc(len + 1);
                fread(data, 1, len, fp);
                data[len] = '\0';
                fclose(fp);

                cJSON *root = cJSON_Parse(data);
                cJSON *user;                 
                
                printf("%s\n", id_);

                cJSON_ArrayForEach(user, root) {
                    char *uid = cJSON_GetObjectItem(user, "id")->valuestring;
                    if(strcmp(uid,id_ )==0)
                    {
                        
                        char *name = cJSON_GetObjectItem(user, "name")->valuestring;
                        int age = cJSON_GetObjectItem(user, "age")->valueint;
                        char *phone = cJSON_GetObjectItem(user, "phone")->valuestring;
                        char *addr = cJSON_GetObjectItem(user, "addr")->valuestring;
                        User user_info;
                        
                        strcpy(user_info.id ,uid);
                        strcpy(user_info.name, name);
                        user_info.age = age;
                        strcpy(user_info.phone, phone);
                        strcpy(user_info.addr , addr);
                        

                        write(client_socket, user_info.id, sizeof(user_info.id));
                        write(client_socket, user_info.name, sizeof(user_info.name));
                        write(client_socket, &user_info.age, sizeof(user_info.age));
                        write(client_socket, user_info.phone, sizeof(user_info.phone));
                        write(client_socket, user_info.addr, sizeof(user_info.addr));

                        printf("%s\n",user_info.name);
                        printf("%d\n",user_info.age);
                        printf("%s\n",user_info.phone);
                        printf("%s\n",user_info.addr);

                    }
                    else{
                        printf("유저가 없거나 가져올수 없습니다.\n");
                    }
                 }
            }
            if (strcmp(action, "2") == 0) // 도서검색하기
            {
                char key[50], val[100];
                read(client_socket, key, sizeof(key));
                read(client_socket, val, sizeof(val));
                printf("%s %s\n",key, val);
                Book *p_found = NULL;
                int count = search_books_count(key, val);
                p_found = malloc(sizeof(Book)*count);
                write(client_socket, &count, sizeof(int));
                search_books(key, val, p_found);
                for (int i = 0; i < count; i++)
                {
                    write(client_socket, &p_found[i], sizeof(Book));
                }
                free(p_found);
            }
            
            else if (strcmp(action, "5") == 0)
            {
                break;
            }                                                                                                                                                                                                                                                                                                                                                                                                                                              
        }
    }
    else if (result == 2 && strcmp(cmd, "login") == 0) { //관리자로 로그인했을때 기능
        while (1) {
            char action[16];
            read(client_socket, action, sizeof(action));  // 사용자 요청
            action[strcspn(action, "\n")] = '\0';
            if (strcmp(action, "1") == 0)
            {
                char somi[16];
                read(client_socket, somi, sizeof(somi));  // 사용자 요청
                somi[strcspn(somi, "\n")] = '\0';
                if (strcmp(somi, "1") == 0) //모든도서확인하기
                {

                    send(client_socket,&book_count,sizeof(int),0);
            
                    for (int i = 0; i < book_count; i++)
                    {
                        write(client_socket, &books[i], sizeof(Book));
                    }

                }
                if (strcmp(somi, "2") == 0) // 도서검색하기
                {
                    char key[50], val[100];
                    read(client_socket, key, sizeof(key));
                    read(client_socket, val, sizeof(val));
                    printf("%s %s\n",key, val);
                    Book *p_found = NULL;
                    int count = search_books_count(key, val);
                    p_found = malloc(sizeof(Book)*count);
                    write(client_socket, &count, sizeof(int));
                    search_books(key, val, p_found);
                    for (int i = 0; i < count; i++)
                    {
                        write(client_socket, &p_found[i], sizeof(Book));
                    }
                    free(p_found);
                }
                else if (strcmp(somi, "3") == 0) // 도서수정하기
                {
                    Book b;
                    read(client_socket, &b, sizeof(Book));
                    result = add_book(b);
                    write(client_socket, &result, sizeof(int));
                } 
                else if (strcmp(somi, "4") == 0)
                {
                    char isbn[200];
                    read(client_socket, isbn, sizeof(char));
                    result = delete_book(isbn);
                    write(client_socket, &result, sizeof(int));
                } 
                else if (strcmp(somi, "5") == 0)
                {
                    Book b;
                    read(client_socket, &b, sizeof(Book));
                    result = modify_book(b);
                    write(client_socket, &result, sizeof(int));
                }
                else if (strcmp(somi, "6") == 0)
                {
                    break;
                }
            }
            else if (strcmp(action, "2") == 0) // 모든계정관리
            {
                
                send(client_socket,&user_count,sizeof(int),0);

                for (int i = 0; i < user_count; i++)
                {
                    write(client_socket, &Users[i], sizeof(User));
                    
                }
                char sub_action[16];
                read(client_socket, sub_action, sizeof(sub_action));

                if(strcmp(sub_action, "1")==0)
                {

                    
                    //여기서부터
                    char user_id_for_modify[16];
                    
                    // 수정을 원하는 계정의 아이디를 클라이언트로부터 받는다.
                    read(client_socket,user_id_for_modify, sizeof(user_id_for_modify));
                    
                    // 해당하는 유저가 있는지 확인한다.
                    // 해당 하는 유저가 있으면 1을 리턴 아니면 0을 리턴
                    int searched_user; 
                    searched_user = search_user_by_id(user_id_for_modify);
                    
                    send(client_socket, &searched_user, sizeof(int),0);
                    
                    /*
                    Users[user_count]반복문으로 ccnk 아이디의 인덱스를 찾아서
                    해당 인덱스의 id/pw를 따로 저장해둠 
                    그리고 해당 배열을 제거
                    그리고 받은 유저정보를 추가할때 idpw 넣자 
                    */
                    char id_[50];
                    char pw_[50];
                    int flag_for_delete =0;
                    int index_for_delete=0;
                    for (int i=0; i<user_count; i++)
                    {   
                        // user_id_for_modify 와 같은 index를 가져와라!
                        if(strcmp(Users[i].id, user_id_for_modify)==0)
                        {
                            strcpy(id_,Users[i].id);
                            strcpy(pw_,Users[i].pw);
                            index_for_delete = i;
                            flag_for_delete = 1;
                        }
                    }
                    // 클라이언트로부터 유저 정보를 받는ㄷㅏ
                    User modi_user;
                    memset(&modi_user, 0, sizeof(User));
                    
                    read(client_socket, &modi_user, sizeof(modi_user));

                    strcpy(modi_user.id,id_);
                    strcpy(modi_user.pw,pw_);
                    
                    // 해당 아이디를 찾았을때만배열에서 제거
                    if(flag_for_delete)
                    {
                        for (int j=index_for_delete; j<user_count-1; j++)
                        {   
                            Users[j]=Users[j+1];
                        }
                    }
                    user_count= user_count-1;
                    

                    // modi_user.id가 비어있으면 넣으면 안됨
                    if(strcmp(modi_user.id," ")!=0 || modi_user.id !=NULL)
                    {
                        memcpy(&Users[user_count],&modi_user, sizeof(User));
                    }
                    user_count = user_count +1; //억지로 최종카운트를 추가해준다.
            
                    save_user("users.json");

                    // 수정이 완료었다면 클라이언트에 응답으로 1을 넘긴다.
                    searched_user = 1;
                    send(client_socket,&searched_user, sizeof(searched_user),0);
                }//sub_action == 1 
                else if(strcmp(sub_action,"2")==0)
                {
                    
                    //아이디 추가
                    
                    User user_for_add;
                    memset(&user_for_add, 0, sizeof(User));
                    read(client_socket, &user_for_add, sizeof(user_for_add));

                    // 구조체 끝부분에 넣는다.
                    if((strlen(user_for_add.id)>=0) && (user_for_add.id !=NULL))
                    {
                        memcpy(&Users[user_count],&user_for_add, sizeof(User));
                    }
                    user_count = user_count +1;

                    int is_added;
                    // 파일 생성한다.
                    is_added = save_user("users.json");

                    // 클라이언트에 유저 추가 했다는 메시지 보낸다.
                    send(client_socket,&is_added, sizeof(is_added),0);

                }
            }
            else if (strcmp(action, "3") == 0) // 도서관오픈관리
            {
                

                char sub_action[16]="\0";

                //read cmd
                read(client_socket, cmd, sizeof(cmd));
                int mon_and_day[2] = {0,};

               
                

                if(strcmp(cmd,"1")==0) //영업일 설정
                {
                    
                    // read mon_and_day
                    read(client_socket, mon_and_day, sizeof(mon_and_day));
                    // printf("log 827     :%d %d\n",mon_and_day[0], mon_and_day[1] );
                    //영업일 설정 리턴 0 or 1 잘설정되면 1
                    int set_work_result =0;
                    
                    
                    //1 파싱함
                    parsing_json_to_struct_for_bussiness(m4, 4);

                    //2. 설정함
                    set_work_result = set_work_day( mon_and_day[0],  mon_and_day[1], m4);
                    
                    //3. 저장함
                    make_json_file_for_bussiness(m4, 4);

                    

                    
                    printf("log server 1 send set_work_result : %d\n", set_work_result);
                    // send set_work_result
                    send(client_socket, &set_work_result, sizeof(set_work_result),0);

                    // check
                    if(is_open_for_business(m4,mon_and_day[0],  mon_and_day[1]))
                    {
                        printf("%d월 %d일은 영업일 입니다.\n",mon_and_day[0],  mon_and_day[1]);
                    }else{
                        printf("%d월 %d일은 영업이 아닙니다.\n",mon_and_day[0],  mon_and_day[1]);
                    }
                    
                }else if(strcmp(cmd,"2")==0)
                {
                    //휴업일 설정 리턴 0 or 1   
                    

                    // read mon_and_day
                    read(client_socket, mon_and_day, sizeof(mon_and_day));
                    memset(&m4, 0, sizeof(bussiness_month)*31);
                    parsing_json_to_struct_for_bussiness(m4, 4);

                    int set_holy_result =0;


                    //1 파싱함
                    parsing_json_to_struct_for_bussiness(m4, 4);

                    //2. 설정함
                    set_holy_result = set_holiday( mon_and_day[0],  mon_and_day[1], m4);
                    
                    //3. 저장함
                    make_json_file_for_bussiness(m4, 4);

                    send(client_socket, &set_holy_result, sizeof(set_holy_result),0);

                    if(is_open_for_business(m4,mon_and_day[0],  mon_and_day[1]))
                    {
                        printf("%d월 %d일은 영업일 입니다.\n",mon_and_day[0],  mon_and_day[1]);
                        
                    }else{
                        printf("%d월 %d일은 영업이 아닙니다.\n",mon_and_day[0],  mon_and_day[1]);
                        

                    }

                }else if(strcmp(cmd,"3")==0)
                {
                    //해당일이 영업일인지 아닌지 체크

                    // read mon_and_day
                    read(client_socket, mon_and_day, sizeof(mon_and_day));

                    memset(&m4, 0, sizeof(bussiness_month)*31);
                    parsing_json_to_struct_for_bussiness(m4, 4);
                    
                    for(int i=0; i<31; i++)
                    {
                        printf("logs 1026 for %s\n", m4[i].date);
                    }

                    int result;
                    if(is_open_for_business(m4,mon_and_day[0],  mon_and_day[1]))
                    {
                        printf("%d월 %d일은 영업일 입니다.\n",mon_and_day[0],  mon_and_day[1]);
                        result = 1;
                        
                    }else{
                        printf("%d월 %d일은 영업이 아닙니다.\n",mon_and_day[0],  mon_and_day[1]);
                        result = 0;

                    }
                    printf("logs 1040 : %d\n",result);

                    send(client_socket, &result, sizeof(result),0);


                }



                break;
            }
            else if (strcmp(action, "4") == 0) // 대출자정보
            {
                break;
            }
            else if (strcmp(action, "5") == 0) // 로그아웃
            {
                break;
            }   
        }
    }
    else if (result == 3 && strcmp(cmd, "login") == 0) { //사서로 로그인했을때 기능
        while (1) {
            char action[16];
            read(client_socket, action, sizeof(action));  // 사용자 요청
            action[strcspn(action, "\n")] = '\0';

            if (strcmp(action, "1") == 0)
            {
                break;
            }
            else if (strcmp(action, "2") == 0)
            {
                
                while(1)
                {
                    printf("사서가 오픈관리메뉴를 선택했습니다. \n");
                
                    bussiness_month m4[31];
                    set_calendar(m4, 4);
                    make_json_file_for_bussiness(m4,4); //이 명령을 하면 json파일이 리셋됨
    
                    time_t timer = time(NULL);
                    struct tm* t = localtime(&timer);

                     //오늘 날짜를 문자열로 바꿈
                     char day[10];
                     sprintf(day, "%d", t->tm_mday);
                     char holiday[50];

                    for(int i=1;i<31;i++){
                    // printf("log 1:  날짜%s %s요일 %d\n", m4[i].date, m4[i].day_,m4[i].is_open);
                    
                    // printf("%s\n", m4[i].date);
                    // printf("%d\n", t->tm_m);

                        if(strstr(m4[i].date,day))
                        {
                            printf("인덱스는? %d %s일 쉬는지?%d \n", i, m4[i].date,  m4[i].is_open);
                            if(m4[i].is_open)
                            {
                                strcpy(holiday, "영업일 입니다.");
                            }else
                            {   
                                strcpy(holiday, "휴일 입니다.");
                            }
                        }
                    
                    }
                    printf("금일은  %s \n",holiday);

                    send(client_socket,holiday,sizeof(holiday),0);
                    break;
                }//while(1)문끝
               
            }
            else if (strcmp(action, "3") == 0) // 모든계정관리
            {
                send(client_socket,&user_count,sizeof(int),0);
                
                for (int i = 0; i < user_count; i++)
                {
                    write(client_socket, &Users[i], sizeof(User));
                }
            }
            else if (strcmp(action, "5") == 0) // 로그아웃
            {
                break;
            }   
        }
    }

    close(client_socket);  // 소켓 종료
    return NULL;
}

// 메인 함수 - 서버 실행
int main() {
    load_books("DATA.json");  // 도서 데이터 불러오기
    load_user("users.json");  // 유저 데이터 불러오기

    // for (int i=0;i<book_count;i++)
    // {
    // printf(" %d\n %s\n %s\n %s\n %d\n %d\n %s\n %s\n %s\n %s\n %d\n", books[i].no, books[i].title, books[i].author, books[i].publisher, books[i].pub_year,
    // books[i].num_books, books[i].isbn, books[i].extra_n, books[i].kdc, books[i].kdc_subject, books[i].loan_frequency);
    // }
    int server_fd = socket(PF_INET, SOCK_STREAM, 0);  // 소켓 생성
    struct sockaddr_in address = {0};                 // 주소 구조체 초기화
    address.sin_family = AF_INET;                     // IPv4 사용
    address.sin_addr.s_addr = INADDR_ANY;             // 모든 IP 허용
    address.sin_port = htons(PORT);                   // 포트 설정

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));  // 바인딩
    listen(server_fd, 5);                            // 연결 대기
    printf("서버 실행 중...\n");

    while (1) {
        int *client_socket = malloc(sizeof(int));  // 동적 할당된 소켓 저장용
        socklen_t addrlen = sizeof(address);
        *client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen); // 연결 수락

        pthread_t tid;
        pthread_create(&tid, NULL, client_handler, client_socket);  // 쓰레드 생성
        pthread_detach(tid);  // 쓰레드 자원 자동 해제
    }
    close(server_fd);
    return 0;
}