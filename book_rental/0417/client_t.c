#include <stdio.h>              // 표준 입출력
#include <stdlib.h>             // 메모리/문자열 함수
#include <string.h>             // 문자열 처리 함수
#include <unistd.h>             // read(), write(), close() 등
#include <netinet/in.h>         // sockaddr_in 구조체 정의
#include <arpa/inet.h>          // inet_pton() 함수
#pragma pack(1)
#define SIZE 200
#define MAX_BOOKS 10100 

// 서버와 동일한 도서 구조체 정의


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


#define PORT 9000  // 서버 포트

void clear_newline(char *str) {
    str[strcspn(str, "\n")] = 0; // Remove the newline character
}

int main() {
    int sock;
    struct sockaddr_in serv_addr = {0};
    char choice[10], id[50], pw[50];
    char nickname[50], phone[50], address[100];
    int year;

    while(1) {
        printf("1.로그인\n2.회원가입\n3.대출하기\n4.반납하기>> ");
        fgets(choice, sizeof(choice), stdin);
        clear_newline(choice); // Remove the newline from choice input

        printf("ID: "); fgets(id, sizeof(id), stdin); clear_newline(id);
        printf("PW: "); fgets(pw, sizeof(pw), stdin); clear_newline(pw);

        while(1) {
            // 회원가입일 경우 추가 정보 입력
            if (choice[0] == '2') {
                printf("이름: "); fgets(nickname, sizeof(nickname), stdin); clear_newline(nickname);
                printf("나이: "); scanf("%d", &year); getchar();
                if (year < 10){
                    printf("10살 이하는 가입이안됩니다.\n");
                    break;
                }
                printf("전화번호: "); fgets(phone, sizeof(phone), stdin); clear_newline(phone);
                printf("주소: "); fgets(address, sizeof(address), stdin); clear_newline(address);
            }

            sock = socket(AF_INET, SOCK_STREAM, 0);
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(PORT);
            inet_pton(AF_INET, "10.10.20.104", &serv_addr.sin_addr);
            connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //서버의 accept로 가는 

            if (choice[0] == '1') send(sock, "login", 16, 0);
            else send(sock, "register", 16, 0);
            send(sock, id, sizeof(id), 0);
            send(sock, pw, sizeof(pw), 0);

            // 회원가입일 경우 추가 정보 전송
            if (choice[0] == '2') {
                send(sock, nickname, sizeof(nickname), 0);
                send(sock, &year, sizeof(int), 0);
                send(sock, phone, sizeof(phone), 0);
                send(sock, address, sizeof(address), 0);
                printf("회원가입이 완료되었습니다.\n");
                break;
            }

            int result;
            read(sock, &result, sizeof(int));
            if (result != 1 && result != 2 && result != 3) {
                printf("없는 계정이거나 아이디 혹은 비밀번호가 틀리셨습니다.\n");
                close(sock);
                sleep(1);
                system("clear");
                break;
            }

            printf("성공적으로 로그인이 완료되었습니다.%d\n",result);

    // 명령어 루프
            if (result == 1){
                while (1) {
                    char cmd[16];
                    printf("\n명령어 입력 (search/add/delete/modify/exit): ");
                    fgets(cmd, sizeof(cmd), stdin);
                    cmd[strcspn(cmd, "\n")] = 0;
                    send(sock, cmd, sizeof(cmd), 0);

                    if (strcmp(cmd, "search") == 0) 
                    {
                        char key[50], val[150];
                        printf("검색 기준(title/author): ");
                        fgets(key, sizeof(key), stdin);
                        key[strcspn(key, "\n")] = 0;

                        printf("검색어 입력: ");
                        fgets(val, sizeof(val), stdin);
                        val[strcspn(val, "\n")] = 0;

                        send(sock, key, sizeof(key), 0);
                        send(sock, val, sizeof(val), 0);

                        int count;
                        read(sock, &count, sizeof(int));  // ?

                        if (count>0)
                        {
                            Book *p_results = malloc(sizeof(Book) * MAX_BOOKS);
                            memset(p_results, 0, sizeof(Book) * MAX_BOOKS);
                            read(sock, p_results, sizeof(Book) * count);
                            for (int i = 0; i < count; i++)
                            {
                                printf("[%d] 제목 : %s 글쓴이 : %s 출판사 : %s 출판년 : %d\n", i, p_results[i].title, p_results[i].author, p_results[i].publisher, p_results[i].pub_year);

                            }
                            free(p_results);
                            p_results = NULL;
                        }
                        else
                            printf("검색 결과가 없습니다.\n");
                    
                    // 검색기능 끝 

                    } else if (strcmp(cmd, "add") == 0) {
                        Book b;
                        printf("No: "); scanf("%d", &b.no); getchar();
                        printf("제목: "); fgets(b.title, sizeof(b.title), stdin); b.title[strcspn(b.title, "\n")] = 0;
                        printf("저자: "); fgets(b.author, sizeof(b.author), stdin); b.author[strcspn(b.author, "\n")] = 0;
                        printf("출판사: "); fgets(b.publisher, sizeof(b.publisher), stdin); b.publisher[strcspn(b.publisher, "\n")] = 0;
                        printf("출판년: "); scanf("%d", &b.pub_year); getchar();
                        printf("권 수: "); scanf("%d", &b.num_books); getchar();
                        printf("ISBN: "); fgets(b.isbn, sizeof(b.isbn), stdin); b.isbn[strcspn(b.isbn, "\n")] = 0;
                        printf("부가기호: "); fgets(b.extra_n, sizeof(b.extra_n), stdin); b.extra_n[strcspn(b.extra_n, "\n")] = 0;
                        printf("KDC: "); fgets(b.kdc, sizeof(b.kdc), stdin); b.kdc[strcspn(b.kdc, "\n")] = 0;
                        printf("KDC 주제: "); fgets(b.kdc_subject, sizeof(b.kdc_subject), stdin); b.kdc_subject[strcspn(b.kdc_subject, "\n")] = 0;
                        printf("대출빈도: "); scanf("%d", &b.loan_frequency); getchar();

                        send(sock, &b, sizeof(Book), 0);        //책 추가 요청
                        read(sock, &result, sizeof(int));       // 추가요청에 대한 결과를 받는다.
                        printf(result ? "도서 추가 성공\n" : "도서 추가 실패\n");

                    // 추가 기능끝

                    //삭제 기능
                    } else if (strcmp(cmd, "delete") == 0) {
                        char isbn[100];
                        printf("삭제할 도서 ISBN: "); fgets(isbn, sizeof(isbn), stdin); isbn[strcspn(isbn, "\n")] = 0;
                        send(sock, isbn, sizeof(char), 0);      // 책 삭제 요청
                        read(sock, &result, sizeof(int));       // 삭제요청에 대한 결과를 받는다.
                        printf(result ? "삭제 성공\n" : "삭제 실패\n");

                    } else if (strcmp(cmd, "modify") == 0) {
                        Book b;
                        printf("수정할 도서 ISBN: "); fgets(b.isbn, sizeof(b.isbn), stdin); b.isbn[strcspn(b.isbn, "\n")] = 0;
                        printf("새 No: "); scanf("%d", &b.no); getchar();
                        printf("새 제목: "); fgets(b.title, sizeof(b.title), stdin); b.title[strcspn(b.title, "\n")] = 0;
                        printf("새 저자: "); fgets(b.author, sizeof(b.author), stdin); b.author[strcspn(b.author, "\n")] = 0;
                        printf("새 출판사: "); fgets(b.publisher, sizeof(b.publisher), stdin); b.publisher[strcspn(b.publisher, "\n")] = 0;
                        printf("새 출판년: "); scanf("%d", &b.pub_year); getchar();
                        printf("새 권 수: "); scanf("%d", &b.num_books); getchar();
                        printf("새 부가기호: "); fgets(b.extra_n, sizeof(b.extra_n), stdin); b.extra_n[strcspn(b.extra_n, "\n")] = 0;
                        printf("새 KDC: "); fgets(b.kdc, sizeof(b.kdc), stdin); b.kdc[strcspn(b.kdc, "\n")] = 0;
                        printf("새 KDC 주제: "); fgets(b.kdc_subject, sizeof(b.kdc_subject), stdin); b.kdc_subject[strcspn(b.kdc_subject, "\n")] = 0;
                        printf("새 대출빈도: "); scanf("%d", &b.loan_frequency); getchar();

                        send(sock, &b, sizeof(Book), 0);
                        read(sock, &result, sizeof(int));
                        printf(result ? "수정 성공\n" : "수정 실패\n");

                    } else if (strcmp(cmd, "exit") == 0) {
                        break;
                    }
                }
            }
            else if (result == 2) {
                while(1){
                printf("관리자님 환영합니다.\n");
                printf("1.도서관리\n2.모든계정관리\n3.도서관오픈관리\n4.대출정보\n");
                getchar();
                break;
                }
            }
            else if (result == 3){
                printf("사서님 환영합니다.\n");
                printf("1.도서관리\n2.대출정보\n3.모든계정관리\n4.메세지\n"); 
                getchar();
                break;
            }
            close(sock);
        }
    }
}