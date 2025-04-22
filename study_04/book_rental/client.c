#include <stdio.h>              // 표준 입출력
#include <stdlib.h>             // 메모리/문자열 함수
#include <string.h>             // 문자열 처리 함수
#include <unistd.h>             // read(), write(), close() 등
#include <netinet/in.h>         // sockaddr_in 구조체 정의
#include <arpa/inet.h>          // inet_pton() 함수
#pragma pack(1)
#define SIZE 100
#define MAX_BOOKS 11000
#define PORT 9000  // 서버 포트
#define MAX_LOANS 100  // 대출 가능한 최대 도서 수
#define MAX_USERS 500

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

typedef struct {
    char id[SIZE]; // 유저아이디
    char title[SIZE];  // 제목
    char author[SIZE]; // 저자 
    char publisher[SIZE]; // 출판사  
    int pubyear; // 출판년
    char isbn[SIZE];  // ISBN
} Book2;

typedef struct {
    char id[50];
    char pw[50];
    char name[50];
    int age;
    char phone[50];
    char addr[50];
    int msc;
}User;
//유저 아이디 이름 나이 핸드폰번호 주소 
typedef struct {

    char date[100];
    char day_[50];
    int is_open;  // 1이면 영업 0이면 휴일
}bussiness_month;


void clear_newline(char *str) {
    str[strcspn(str, "\n")] = 0; // Remove the newline character
}

void phonnum_star(char phone[]){ //핸드폰 중간자리 가운데 별
    for(int i = 4;i < 8; i++){
        phone[i] = "*";             
    }
}

int main() {
    int sock;
    struct sockaddr_in serv_addr = {0};
    char choice[10], id[50], pw[50];
    char nickname[50], phone[50], address[100];
    int year;
    int message_a = 1;
    int plag_exit = 0;
    int d_count = 0;
    Book books[MAX_BOOKS];
    Book2 d_results[MAX_LOANS];  // 대출한 책 저장용
    User Users[MAX_USERS];
    
    while(1)
    {
        printf("1.로그인\n2.회원가입\n3.대출하기\n4.반납하기>> ");
        fgets(choice, sizeof(choice), stdin);
        clear_newline(choice); // Remove the newline from choice input

        printf("ID: "); fgets(id, sizeof(id), stdin); clear_newline(id);
        printf("PW: "); fgets(pw, sizeof(pw), stdin); clear_newline(pw);
        plag_exit = 0;

        while(plag_exit == 0)
        {
            // 회원가입일 경우 추가 정보 입력
            if (choice[0] == '2')
            {
                printf("이름: "); fgets(nickname, sizeof(nickname), stdin); clear_newline(nickname);
                printf("나이: "); scanf("%d", &year); getchar();
                if (year < 10)
                {
                    printf("10살 이하는 가입이안됩니다.\n");
                    break;
                }
                printf("전화번호: "); fgets(phone, sizeof(phone), stdin); clear_newline(phone);
                printf("주소: "); fgets(address, sizeof(address), stdin); clear_newline(address);
            }

            sock = socket(PF_INET, SOCK_STREAM, 0);
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(PORT);
            inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
            connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

            if (choice[0] == '1') send(sock, "login", 16, 0);
            else send(sock, "register", 16, 0);
            send(sock, id, sizeof(id), 0);
            send(sock, pw, sizeof(pw), 0);

            // 회원가입일 경우 추가 정보 전송
            if (choice[0] == '2')
            {
                send(sock, nickname, sizeof(nickname), 0);
                send(sock, &year, sizeof(int), 0);
                send(sock, phone, sizeof(phone), 0);
                send(sock, address, sizeof(address), 0);
                send(sock, &message_a, sizeof(int), 0);
                printf("회원가입이 완료되었습니다.\n");
                break;
            }
            int result;
            read(sock, &result, sizeof(int));
            if (result != 1 && result != 2 && result != 3)
            {
                printf("없는 계정이거나 아이디 혹은 비밀번호가 틀리셨습니다.\n");
                close(sock);
                sleep(1);
                system("clear");
                break;
            }

            printf("성공적으로 로그인이 완료되었습니다.\n");

    // 명령어 루프
            if (result == 1)
            {
                while (plag_exit == 0)
                {
                    char cmd[16];
                    int num = 0;
                    printf("\n1.내정보확인하기\n2.온라인대출하기\n3.메세지보내기\n4.메세지삭제하기\n5.로그아웃");
                    fgets(cmd, sizeof(cmd), stdin);
                    cmd[strcspn(cmd, "\n")] = 0;
                    send(sock, cmd, sizeof(cmd), 0);
                    if (strcmp(cmd,"1") == 0)
                    {
                        User user_info;

                        send(sock, id, sizeof(id), 0);
                        
                        //서버로부터 응답을 받음
                        read(sock, user_info.id, sizeof(user_info.id));
                        read(sock, user_info.name, sizeof(user_info.name));
                        read(sock, &user_info.age, sizeof(int));
                        read(sock, user_info.phone, sizeof(user_info.phone));
                        read(sock, user_info.addr, sizeof(user_info.addr));
                        

                        printf("id :%s\n",id);
                        printf("유저명 :%s\n",user_info.name);
                        printf("나이 :%d\n",user_info.age);
                        printf("전화번호 :%s\n",user_info.phone);
                        printf("주소 :%s\n",user_info.addr);

                        //내 정보를 화면에 출력 + 내 대출목록 

                    }
                    else if (strcmp(cmd, "2") == 0)
                    {
                        char key[50], val[100];
                        printf("검색 기준(title/author): ");
                        fgets(key, sizeof(key), stdin);
                        key[strlen(key) - 1] = '\0';
                        // key[strcspn(key, "\n")] = 0;
                        printf("검색어 입력: ");
                        fgets(val, sizeof(val), stdin);
                        val[strlen(val) - 1] = '\0';
                        // val[strcspn(val, "\n")] = 0;
                        send(sock, key, sizeof(key), 0);
                        send(sock, val, sizeof(val), 0);
                        int count;

                        // memset(p_results, 0, sizeof(Book));
                        read(sock, &count, sizeof(int));
                        Book *p_results = NULL;
                        p_results = malloc(sizeof(Book)*count);
                        if (count>0)
                        {
                            for (int i = 0; i < count; i++)
                            {
                                read(sock, &p_results[i], sizeof(Book));
                            }
                            for (int i = 0; i < count; i++)
                            {
                                printf("[%d] 제목 : %s 글쓴이 : %s 출판사 : %s 출판년 : %d ISBN %s\n", i, p_results[i].title, p_results[i].author, p_results[i].publisher, p_results[i].pub_year,p_results[i].isbn);
                                
                            }
                            printf("대출할 번호를 입력해주세요: ");
                            scanf("%d", &num); 
                            getchar();
                            strcpy(d_results[d_count].title, p_results[num].title);
                            strcpy(d_results[d_count].author, p_results[num].author);
                            strcpy(d_results[d_count].publisher, p_results[num].publisher);
                            d_results[d_count].pubyear = p_results[num].pub_year;
                            strcpy(d_results[d_count].isbn, p_results[num].isbn);
                            strcpy(d_results[d_count].id, id); // 유저 ID 저장
                            printf("권수를 입력해주세요: ");
                            int num_2;
                            scanf("%d", &num_2); 
                            getchar();
                            printf(">> 대출 내역:\n");
                            for (int i = 0; i <= d_count; i++) {
                                printf("ID: %s | 제목: %s | 저자: %s | 출판사: %s | 출판년: %d | ISBN: %s | 권수: %d\n",
                                    d_results[i].id, d_results[i].title, d_results[i].author,
                                    d_results[i].publisher, d_results[i].pubyear,
                                    d_results[i].isbn, num_2);
                            }
                            d_count++;
                        }
                        else
                        printf("검색 결과가 없습니다.\n");
                        free(p_results);
                    } 
                    else if (strcmp(cmd, "5") == 0)
                    {
                        plag_exit = 1;
                        break;
                    }
                }
            }
            else if (result == 2)
            {
                while(plag_exit == 0){
                    printf("관리자님 환영합니다.\n");
                    printf("1.도서관리\n2.모든계정관리\n3.도서관오픈관리\n4.대출자정보\n5.로그아웃\n");
                    char cmd[16];
                    fgets(cmd, sizeof(cmd), stdin);
                    cmd[strcspn(cmd, "\n")] = 0;
                    send(sock, cmd, sizeof(cmd), 0);
                    if (strcmp(cmd, "1") == 0) // 도서관리
                    {   
                        char cmp[16];
                        printf("1.도서목록\n2.도서검색\n3.도서수정\n4.도서추가\n5.도서삭제\n6.돌아가기");
                        fgets(cmp, sizeof(cmp), stdin);
                        cmp[strcspn(cmp, "\n")] = 0;
                        send(sock, cmp, sizeof(cmp), 0);
                        if(strcmp(cmp, "1") == 0)
                        {
                            int count;
                            read(sock, &count, sizeof(int));
                            Book *all = NULL;
                            all = malloc(sizeof(Book)*count);
                            if (count>0)
                            {
                                for (int i = 0; i < count; i++)
                                {
                                    read(sock, &all[i], sizeof(Book));
                                }
                                for (int i = 0; i < count; i++)
                                {
                                    printf(" %d 제목: %s ,저자: %s ,출판사: %s ,출판년: %d ,권: %d ,ISBN: %s ,부가기호: %s ,KDC: %s ,KDC주제명: %s ,대출빈도: %d\n", 
                                    all[i].no, all[i].title, all[i].author, all[i].publisher, all[i].pub_year,
                                    all[i].num_books, all[i].isbn, all[i].extra_n, all[i].kdc, all[i].kdc_subject, all[i].loan_frequency);
                                }
                            }
                            else
                            printf("검색 결과가 없습니다.\n");
                            free(all);
                        }
                        else if(strcmp(cmp, "2") == 0) // 검색기능
                        {
                            char key[50], val[100];
                            printf("검색 기준(title/author): ");
                            fgets(key, sizeof(key), stdin);
                            key[strlen(key) - 1] = '\0';
                            // key[strcspn(key, "\n")] = 0;
                            printf("검색어 입력: ");
                            fgets(val, sizeof(val), stdin);
                            val[strlen(val) - 1] = '\0';
                            // val[strcspn(val, "\n")] = 0;
                            send(sock, key, sizeof(key), 0);
                            send(sock, val, sizeof(val), 0);
                            int count;
    
                            // memset(p_results, 0, sizeof(Book));
                            read(sock, &count, sizeof(int));
                            Book *p_results = NULL;
                            p_results = malloc(sizeof(Book)*count);
                            if (count>0)
                            {
                                for (int i = 0; i < count; i++)
                                {
                                    read(sock, &p_results[i], sizeof(Book));
                                }
                                for (int i = 0; i < count; i++)
                                {
                                    printf("[%d] 제목 : %s 글쓴이 : %s 출판사 : %s 출판년 : %d ISBN %s\n", i-1, p_results[i].title, p_results[i].author, p_results[i].publisher, p_results[i].pub_year,p_results[i].isbn);
                
                                }
                            }
                            else
                            printf("검색 결과가 없습니다.\n");
                            free(p_results);
                        }
                        else if (strcmp(cmp, "3") == 0) //도서수정
                        {
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
    
                        }
                        else if (strcmp(cmp, "4") == 0) // 도서추가
                        {
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
    
                            send(sock, &b, sizeof(Book), 0);
                            read(sock, &result, sizeof(int));
                            printf(result ? "도서 추가 성공\n" : "도서 추가 실패\n");
    
                        }
                        else if (strcmp(cmp, "5") == 0) // 도서삭제
                        {
                            char isbn[100];
                            printf("삭제할 도서 ISBN: "); fgets(isbn, sizeof(isbn), stdin); isbn[strcspn(isbn, "\n")] = 0;
                            send(sock, isbn, sizeof(char), 0);
                            read(sock, &result, sizeof(int));
                            printf(result ? "삭제 성공\n" : "삭제 실패\n");
                        }
                        else if (strcmp(cmp, "6") == 0) // 돌아가기
                        {
                            break;
                        }
                    }
                    if (strcmp(cmd, "2") == 0) // 모든계정관리
                    {
                        int count_2 = 0;
                        read(sock, &count_2, sizeof(int));
                        User *all_2 = NULL;
                        all_2 = malloc(sizeof(User)*count_2);
                        if (count_2>0)
                        {
                            for (int i = 0; i < count_2; i++)
                            {
                                read(sock, &all_2[i], sizeof(User));
                            }
                            for(int i = 2;i<count_2;i++){
                                printf("%d.아이디 %s, 이름 %s, 나이 %d, 핸드폰번호 %s 주소 %s\n",i-1,all_2[i].id,all_2[i].name,all_2[i].age,all_2[i].phone,all_2[i].addr);
                            }
                            
                            printf("\n1. 계정 수정\n2. 계정 추가\n3. 돌아가기\n선택: ");
                            char subcmd[10];
                            fgets(subcmd, sizeof(subcmd), stdin);
                            subcmd[strcspn(subcmd, "\n")] = 0;
                            send(sock, subcmd, sizeof(subcmd), 0);

                            if(strcmp(subcmd, "1") == 0) {
                                printf("수정할 계정 번호 선택: ");
                                int user_num;
                                scanf("%d", &user_num); getchar();
                                if(user_num < 1 || user_num > count_2-2) {
                                    printf("잘못된 계정 번호입니다.\n");
                                } else {
                                    User modified_user = all_2[user_num+1];
                                    printf("새로운 정보를 입력하세요 (변경하지 않으려면 엔터를 누르세요)\n");
                                    
                                    char temp[50];
                                    printf("이름 (%s): ", modified_user.name);
                                    fgets(temp, sizeof(temp), stdin);
                                    temp[strcspn(temp, "\n")] = 0;
                                    if(strlen(temp) > 0) strcpy(modified_user.name, temp);

                                    printf("나이 (%d): ", modified_user.age);
                                    fgets(temp, sizeof(temp), stdin);
                                    temp[strcspn(temp, "\n")] = 0;
                                    if(strlen(temp) > 0) modified_user.age = atoi(temp);

                                    printf("전화번호 (%s): ", modified_user.phone);
                                    fgets(temp, sizeof(temp), stdin);
                                    temp[strcspn(temp, "\n")] = 0;
                                    if(strlen(temp) > 0) strcpy(modified_user.phone, temp);

                                    printf("주소 (%s): ", modified_user.addr);
                                    fgets(temp, sizeof(temp), stdin);
                                    temp[strcspn(temp, "\n")] = 0;
                                    if(strlen(temp) > 0) strcpy(modified_user.addr, temp);

                                    send(sock, &user_num, sizeof(int), 0);
                                    send(sock, &modified_user, sizeof(User), 0);

                                    int result;
                                    read(sock, &result, sizeof(int));
                                    if(result == 1) {
                                        printf("계정 정보가 성공적으로 수정되었습니다.\n");
                                    } else {
                                        printf("계정 정보 수정에 실패했습니다.\n");
                                    }
                                }
                            }
                            else if(strcmp(subcmd, "2") == 0) {
                                User new_user;
                                printf("새 계정 정보를 입력하세요\n");
                                
                                printf("아이디: ");
                                fgets(new_user.id, sizeof(new_user.id), stdin);
                                new_user.id[strcspn(new_user.id, "\n")] = 0;
                                
                                printf("비밀번호: ");
                                fgets(new_user.pw, sizeof(new_user.pw), stdin);
                                new_user.pw[strcspn(new_user.pw, "\n")] = 0;
                                
                                printf("이름: ");
                                fgets(new_user.name, sizeof(new_user.name), stdin);
                                new_user.name[strcspn(new_user.name, "\n")] = 0;
                                
                                printf("나이: ");
                                scanf("%d", &new_user.age); getchar();
                                
                                printf("전화번호: ");
                                fgets(new_user.phone, sizeof(new_user.phone), stdin);
                                new_user.phone[strcspn(new_user.phone, "\n")] = 0;
                                
                                printf("주소: ");
                                fgets(new_user.addr, sizeof(new_user.addr), stdin);
                                new_user.addr[strcspn(new_user.addr, "\n")] = 0;
                                
                                new_user.msc = 0;  // 초기 메시지 카운트는 0으로 설정
                                
                                send(sock, &new_user, sizeof(User), 0);
                                
                                int result;
                                read(sock, &result, sizeof(int));
                                if(result == 1) {
                                    printf("새 계정이 성공적으로 추가되었습니다.\n");
                                } else {
                                    printf("계정 추가에 실패했습니다.\n");
                                }
                            }
                        }
                        else
                        printf("검색 결과가 없습니다.\n");
                        free(all_2);
                    }  
                    if (strcmp(cmd, "3") == 0) // 도서관오픈관리
                    {
                       
                    }
                    if (strcmp(cmd, "4") == 0) // 대출자정보
                    {
                       
                    }
                    if (strcmp(cmd, "5") == 0) // 로그아웃
                    {
                        plag_exit = 1;
                        break;
                    }
                }
            }
            else if (result == 3){
                printf("사서님 환영합니다.\n");
                printf("1.도서관리\n2.대출정보\n3.모든계정관리\n4.메세지\n5.로그아웃\n"); 
                char cmd[16];
                fgets(cmd, sizeof(cmd), stdin);
                cmd[strcspn(cmd, "\n")] = 0;
                send(sock, cmd, sizeof(cmd), 0);
                if (strcmp(cmd, "1") == 0) // 도서관리
                {
                    break;
                }
                else if (strcmp(cmd, "2") == 0) // 대출정보
                {
                    break;
                }
                else if (strcmp(cmd, "3") == 0) // 모든계정관리
                {
                    int count_2 = 0;
                    read(sock, &count_2, sizeof(int));
                    User *all_2 = NULL;
                    all_2 = malloc(sizeof(User)*count_2);
                    if (count_2>0)
                    {
                        for (int i = 0; i < count_2; i++)
                        {
                            read(sock, &all_2[i], sizeof(User));
                        }
                        for(int i = 2;i<count_2;i++){
                            printf("%d.아이디 %s, 이름 %s, 나이 %d, 핸드폰번호 %s 주소 %s\n",i-1,all_2[i].id,all_2[i].
                            name,all_2[i].age,all_2[i].phone,all_2[i].addr);
                        }     
                    }
                    else
                    printf("검색 결과가 없습니다.\n");
                    free(all_2);
                }
                else if (strcmp(cmd, "4") == 0) // 메세지
                {
                    break;
                }
                else if (strcmp(cmd, "5") == 0) // 로그아웃
                {
                    plag_exit = 1;
                    break;
                }
            }
            close(sock);
        }
    }
}