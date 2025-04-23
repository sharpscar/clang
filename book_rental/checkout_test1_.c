
#include <limits.h>
#include <time.h>
#include <stdio.h>              // 표준 입출력 함수 사용 (printf, fopen 등)
#include <stdlib.h>             // 동적 메모리 할당 (malloc, free 등)
#include <string.h>             // 문자열 처리 함수 (strcmp, strcpy 등)
#include <unistd.h>             // POSIX API (read, write, close 등)
#include <pthread.h>            // 쓰레드 사용을 위한 헤더
#include <netinet/in.h>         // 소켓 주소 구조체를 위한 헤더 (struct sockaddr_in 등)
#include "cJSON.h"   // JSON 처리 라이브러리 헤더
#include "cJSON.c"

#define MAX_BOOKS 11000           // 도서 최대 등록 수
#define PORT 8080               // 서버가 열릴 포트 번호
#define SIZE 100

/**     대여 구조체
     * 대출을 발생시키기 위한 매개변수
     * 1. user_id <--대출신청한 사용자의 id 
     * 2. books_isbn[] 대출도서의 isbn들 (int형 배열)
     * 3. checkout_date 대여일
     * 4. return_date 반납일
     */
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
    int checkout_id;
    char user_id[50];
    Book books[10]; // 빌린도서의 isbn 문자열
    char checkout_date[50];
    
}checkout_books;


// 전역 도서 배열과 관련 변수 선언
Book books[MAX_BOOKS];          // 도서 목록을 저장할 배열
int book_count = 0;             // 현재 등록된 도서 수
pthread_mutex_t book_mutex = PTHREAD_MUTEX_INITIALIZER;  // 도서 데이터 접근 동기화를 위한 뮤텍스

/**책정보를 가져와서  */
int load_books(const char *filename) ;

/** 현재시간을 가져오는 함수 */
char *  get_current_time();
/** a : 월
 *  b : 일 
 * 요일을 c에 담는 함수 
 * get_current_time 함수에서 참조합니다.
 * */
void solution(int a, int b, char *c);

int main()
{
    int cnt;
    cnt = load_books("DATA.json");
    Book checkout_a_book;
    //내가 찾는책 
    char isbn_[15] ="9791189128562"; // 이건 나중에 매개변수로 받는다! 
    for(int i=0; i<cnt; i++)
    {
        if((strcmp(books[i].isbn, isbn_))==0)
        {
            checkout_a_book = books[i];
        }
        
    }
    printf("%s\n", checkout_a_book.title);
    //담았다.

    //- 유저정보 / 대출일/ 대여정보 를 구조체에 담는다.
    checkout_books cb_myinfo;
    cb_myinfo.checkout_id =1;
    strcpy(cb_myinfo.user_id, "scar");
    strcpy(cb_myinfo.checkout_date,get_current_time());
    cb_myinfo.books[0] = checkout_a_book;

    //대여 json에 담는다 1. checkout_for_server.json 2.checkout_for_record.json
    cJSON *root = cJSON_CreateArray();
    cJSON *c = cJSON_CreateObject();
    cJSON *b = cJSON_CreateObject();
    cJSON *bs = cJSON_CreateArray();

    
    cJSON_AddStringToObject(c,"유저아이디", cb_myinfo.user_id);
    cJSON_AddStringToObject(c,"대출일", cb_myinfo.checkout_date);
    
    cJSON_AddNumberToObject(b, "No", cb_myinfo.books[0].no);
    cJSON_AddStringToObject(b, "제목", cb_myinfo.books[0].title);            // 저자 추가
    cJSON_AddStringToObject(b, "저자", cb_myinfo.books[0].author);
    cJSON_AddStringToObject(b, "출판사", cb_myinfo.books[0].publisher);
    cJSON_AddNumberToObject(b, "출판년", cb_myinfo.books[0].pub_year);
    cJSON_AddNumberToObject(b, "권", cb_myinfo.books[0].num_books);
    cJSON_AddStringToObject(b, "ISBN", cb_myinfo.books[0].isbn);
    cJSON_AddStringToObject(b, "부가기호", cb_myinfo.books[0].extra_n);
    cJSON_AddStringToObject(b, "KDC", cb_myinfo.books[0].kdc);
    cJSON_AddStringToObject(b, "KDC 주제명", cb_myinfo.books[0].kdc_subject);
    cJSON_AddNumberToObject(b, "대출 빈도", cb_myinfo.books[0].loan_frequency);
    
    cJSON_AddItemToArray(root, c);
    cJSON_AddItemToArray(root, b);
    

    char *out = cJSON_Print(root);
    

    char filename_1[30] ="checkout_for_server.json";
    char filename_2[30] ="checkout_for_record.json"; 

    FILE *fp1 = fopen(filename_1, "w");
    fputs(out, fp1);
    fclose(fp1);
    

    FILE *fp2 = fopen(filename_2, "w");
    fputs(out, fp2);
    fclose(fp2);

   
    free(out);
    cJSON_Delete(root);

    //삭제하는 함수 호출 

    //save_books("DATA.json");             // 적용
    
    


    // {
    //     "유저 아이디" :"my_id",
    //     "대출일" : "2025-4-18 19:16:21", 
    //     "대여정보" : 
    //     [{
        //     "No":	2,
        //     "제목":	"달러구트 꿈 백화점 :주문하신 꿈은 매진입니다 ",
        //     "저자":	"지은이: 이미예",
        //     "출판사":	"팩토리나인",
        //     "출판년":	2020,
        //     "권":	10,
        //     "ISBN":	"9791165341909",
        //     "부가기호":	"03810",
        //     "KDC":	"813",
        //     "KDC 주제명":	"소설",
        //     "대출 빈도":	36907
        // },
        // ]

    return 0;
}


char *  get_current_time()
{

    time_t t= time(NULL);
    struct tm tm_ = *localtime(&t);
//    current = (char*)malloc(sizeof(char)*10);
    // memset(current, 0, sizeof(current));
    char str_t[100];
    char *current;
    char yoil[10];

    solution(tm_.tm_mon+1, tm_.tm_mday, yoil);
    // printf("ttttttttttttttttttttttttt%s", yoil);
    sprintf(str_t,"%d-%d-%d %d:%02d:%02d", 
                tm_.tm_year+1900,
                tm_.tm_mon+1,
                tm_.tm_mday,
                tm_.tm_hour,
                tm_.tm_min,
                tm_.tm_sec
            );

    // printf("%s", str_t);
    current = &str_t;
    // strcpy(*current, str_t);
    // printf("%s", current);

    return current;

}

/** 4월달 요일을 뱉는 함수 */
void solution(int a, int b, char *c) {
    char *DayOfTheWeek[] = {"일","월","화","수","목", "금","토"};
    int DayOfMonth[12] =  {31,28,31,30,31,30,31,31,30,31,30,31};
    int Total = 0;
    // printf("%d\n", a);
   char the_day[10];
   while(a>0){
    Total +=DayOfMonth[--a];
   }   
   Total += b;
   
   strcpy(c,DayOfTheWeek[Total%7] );

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