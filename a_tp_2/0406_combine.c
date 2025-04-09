#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>  // 디렉토리 읽기용
#include "struct_member.h"
#define MAX_MEMBERS 100

char new_id [40];
char new_password[20];
char new_name[20];
int new_age;
char new_phone_num[40];

int found_account[MAX_MEMBERS];
int articles_cnt;
int members_cnt;
int account_cnt;
int admin_articles_cnt;

member new_mem[MAX_MEMBERS]; 
article articles[300];
article admin_articles[300]; 

void print_member_page(member *arr, int total_count);
int print_main_menu();  //메인메뉴 프린트(0)
int login(member *a);   // 로그인하는 함수(0)
void main_menu2(int login_index);  //로그인 후 메인메뉴 프린트 (0)
void admin_main(); //관리자모드 메인메뉴 프린트
int join_id_check(member *a); // 아이디 가입 조건 확인하는 함수 (0)
int join_check_password();  // 비밀번호 확인 함수 (0)
int save_phonenum();  //휴대폰번호 양식에 맞게 저장하는 함수(0)
void masking_phonenum(member *a);  //휴대폰 번호 가운데 마스킹하는 함수(0)
void sign_up();  //회원가입(조건 맞을 때 csv파일 추가)(0)
void csv_to_struct_mem(); // 회원csv 파일 -> 구조체 new_mem 파일에 담는 함수 (0)
int search_members_main(); //회원정보 조회 메인함수
void search_mem_name();  // 회원정보 이름으로 조회하는 함수
void show_my_info(int login_index); //내정보 확인하는 함수
void admin_can_check_account_info(member *a);  //관리자가 모든 정보를 출력하여 보는 함수
void order_by_account_name();  //멤버이름으로 정렬하기 위한 함수
int comfunc_by_member_name(const void *a, const void *b);  // qsort 정렬을 위하여 정렬 기준 비교 // qsort(정렬할_배열, 개수, sizeof(하나의_요소), 비교함수);
int comfunc_by_member_id(const void *a, const void *b);  //아이디 정렬 하기 위해서 만듦
void retrieve_id_from_member(int* found_account, char id_account[]);  //검색된 유저만 temp 구조체에 담아서 출력합니다
void delete_a_article_from_admin_articles(int del_index);
void store_to_admin_article_struct();
void store_to_article_struct();
void write_a_admin_article();
article get_input_for_write_article();
void show_article_list();
void masking_user_phonenum(member *a, int login_index);
void show_paging();
int log_out_or_exit();
void write_user_article_with_number(const char *user_id);
void print_member_page(member *arr, int total_count);
int getTotalLine(char *name);

int main(){

    while(1){
        int main_menu_choice = 0;
        int user_num_choice = 0;
        int sign_up_choice = 0; //1 ->돌아가기
        csv_to_struct_mem();

        main_menu_choice = print_main_menu();  //메인메뉴 호출 후 선택지 저장
        if(main_menu_choice == 1){  //로그인
            user_num_choice = login(new_mem);
            if(user_num_choice == 0){  //관리자모드
                admin_main();
            }
            else if(user_num_choice !=0){  //아닌 메인
                main_menu2(user_num_choice);
            }
        }
        if(main_menu_choice == 2){  //회원가입
            sign_up_choice = join_id_check(new_mem);
            if (sign_up_choice == 1){  //exit를 입력하여 돌아가기 선택하면
                continue;
            }
            sign_up_choice = join_check_password();
            if(sign_up_choice == 1){ //exit를 입력하여 돌아가기 선택하면
                continue;
            }
            sign_up_choice = save_phonenum();
            if(sign_up_choice == 1){ //exit를 입력하여 돌아가기 선택하면
                continue;
            }
            sign_up();
            continue;
        }
    }
}

int print_main_menu(){
    int choice;
    puts(" ~ 신난다 ~ 재미나다 ! ~ 우리들의 버디버디 ~ ");
    puts("---------------- LOG IN -------------------");
    puts("1:\t\t로그인");
    puts("2:\t\t회원가입");
    printf(" > > > ");
    scanf("%d",&choice);
    return choice;
}

void main_menu2(int login_index) {
    int main_menu2_choice;
    char choice;
    char search_id[30];
    char *login_id = new_mem[login_index].id;

    printf("나: %s", new_mem[login_index].name);
    while (1) {
        printf("\n===== 메인 메뉴 =====\n");
        printf("w. 텍스트 만들기\n");
        printf("a. 텍스트 목록\n");
        printf("t. 텍스트 보내기\n");
        printf("f. 유저 찾기\n");
        printf("c. 내 정보 확인하기\n");
        printf("z. 종료하기\n");
        printf("선택 >> ");
        getchar();
        scanf(" %c", &choice);

        switch (choice) {
            case 'w':
                write_user_article_with_number(login_id);  // 유저 ID 넘기기
                break;
            case 'a':
                // show_article_list(login_id);
                show_paging();
                break;
            case 't':
                // send_text(login_id);

                break;
            case 'f':
            main_menu2_choice = search_members_main();
                if(main_menu2_choice == 1){
                    printf("검색할 ID를 입력하세요: ");
                    getchar();
                    scanf("%s", search_id);
                    retrieve_id_from_member(found_account,search_id);
                }
                if(main_menu2_choice == 2){
                    search_mem_name();
                } 
                break;
            case 'c':
                show_my_info(login_index);
                break;
            case 'z':
            main_menu2_choice = log_out_or_exit();
                if(main_menu2_choice == 1){
                    return;
                }
                else if(main_menu2_choice == 2){
                    exit(1);
                }
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

int login(member *a){
    system("clear");
    char login_id[50];
    char login_pw[50];
    int flag_id = 0;
    int user_num = 0;



    while(1){
        puts("ID: ");
        getchar();
        scanf("%s",login_id);

        for(int i = 0; i < 100; i++){
            if (strcmp(login_id,a[i].id)==0){
                flag_id = 1;
                user_num = i;
            }
        }
        if(flag_id != 1){
            printf("없는 아이디 입니다.");   
            continue;
        }
        puts("PASSWORD: ");
        getchar();
        scanf("%s",login_pw);
        
        if(strcmp(login_pw,a[user_num].password)==0){
            printf("로그인 성공: %s님, 안녕하세요!\n",a[user_num].name);
            return user_num;
        }
        else{
            printf("비밀번호가 일치하지 않습니다. 다시 입력하세요\n");
            continue;
        }
    }
}

int join_id_check(member *a){

    char join_id[50]; // 아이디 입력할때
    //회원가입시 아이디 입력조건
    while(1){
        int flag_id = 0; // 문자열 비교하기위한 플래그
        int flag_join = 0;
        int flag_korean = 0;
        int input_id = 0; // 아이디 입력시 영문자와 숫자 받을 변수

        printf("ID를 입력하세요(나가기>exit): ");
        getchar();
        scanf("%s",join_id);
        if(strcmp(join_id,"exit")==0){
            printf("메인화면으로 돌아갑니다.\n");
            return 1;
        }
        //회원가입 아이디 입력 (형식에 맞는지 검사) 맞으면 1
        for(int i=0; i<strlen(join_id); i++){
            if((join_id[i] >= '0' && join_id[i] <= '9') || (join_id[i] >= 'a' && join_id[i] <= 'z') || (join_id[i] >= 'A' && join_id[i] <= 'Z')){
                input_id ++; 
            }
            else{
                flag_korean = 1;
            }
        }
        if(input_id == strlen(join_id)){
            flag_join = 1; // 회원가입시 아이디 양식에 맞게 잘 입력했는지 확인하는 플래그,
        }
        else{
            printf("영문과 숫자를 조합하여 작성하세요.\n");
            continue;
        }

        //회원가입 입력한 아이디가 중복이 없는지 검사. 중복이면 1
        for(int i = 0; i <= account_cnt; i++){
            if (strcmp(join_id,a[i].id)==0){
                flag_id = 1; 
            }
        }
        //입력한 아이디가 형식이 맞고(flag_join == 1), 중복이 없고(flag id == 0) ->회원가입 가능한 조건
        if(strlen(join_id) > 4){// ID 다섯글자이상.
            if((flag_join == 1) && (flag_id != 1)){
                printf("ID를 사용할수있습니다.\n");
                strcpy(new_id,join_id);  //안됨
                break;
            }
            else if(flag_id == 1){
                printf("사용중인 아이디가 존재합니다. 다시 입력!\n");
                    continue;
            }
        }
        else{
            printf("5글자이상\n");
        }
    }
}

int join_check_password(){
    int lower_, upper_,digit_, spec_; // 소문자, 대문자, 숫자
    char password[20]; // 비밀번호 입력하는 배열이구요
    int special[20] = {0}; // 특수문자배열. 문자를 "숫자화" 하여 아스키로 인식하게 하는 배열
    int korean_ = 0;  //한글 확인할때
    char check_pw[20] = {0};  //비밀번호 확인할때

    while(1){
        lower_= upper_ = digit_ = spec_ =0; //초기화

        printf("비밀번호를 입력하세요(나가기>exit): ");
        getchar();
        scanf("%s",password);

        if(strcmp(password,"exit")==0){
            printf("메인화면으로 돌아갑니다.\n");
            return 1;
        }

        //특수문자를 입력했을때 아스키코드로 나타나게 하기 위한것. 문자"!"를 --> 정수 배열에 34 로 저장
        for(int i =0; i<strlen(password); i++){
            special[i] = password[i];
        }

        // 숫자, 대문자, 소문자, 특수문자를 각 변수에 담아냄
        for(int i=0; i<strlen(password); i++){
            if(password[i] >= '0' && password[i] <= '9')
                digit_ = 1;
            else if(password[i] >= 'A' && password[i] <= 'Z')
                upper_ = 1;
            else if(password[i] >= 'a' && password[i] <= 'z')
                lower_ = 1;
            else if((special[i] >= 33 && special[i] <= 38) || special[i] == 64) 
                spec_ = 1;
            else {
                korean_ = 1;
            }
        }
        if(korean_ == 1) { // 한글이면 먼저 걸러주기
            korean_ = 0; // 초기화 순서 중요 !!! 초기화먼저 해줘야 korean = 1값이 남아있지 않고 while문으로 돌아감
            printf("한글입력 하지마세요.\n");
            continue;
        }
        else if((digit_ == 1) && (upper_ == 1) && (lower_ == 1) && (spec_ == 1) && (strlen(password)>=6)){
           
            printf("적절한 암호입니다.\n");

            while(1){
                printf("비밀번호확인: ");
                getchar();
                scanf("%s",check_pw);
            
                if(strcmp(password,check_pw) == 0){
                    printf("비밀번호가 일치합니다.\n");
                    strcpy(new_password, password);
                    break;
                }
                else{
                    printf("비밀번호 불일치\n");
                }
            }
            break;
        }
        else{
            printf("6자리 이상. 숫자, 대문자, 소문자, 특수문자(!,#,$,%%,&,@) 모두 사용하여 입력하세요.\n");
        }
    }
}

int save_phonenum() {
    char phonenum[40];
    char clean_phonenum[40];
    int j = 0;  //clean_phonenum에 접근하기위한 인덱스

    puts("전화번호 입력(나가기>exit): ");
    getchar();
    scanf("%s", phonenum);  // 전화번호 입력 받기
    if(strcmp(phonenum,"exit")==0){
        printf("메인화면으로 돌아갑니다.\n");
        return 1;
    }

    // 원래 문자열 돌면서 '-'가 아니면 클린넘버에 넣기
    for (int i = 0; i < strlen(phonenum); i++) {
        if (phonenum[i] != '-') {
            clean_phonenum[j++] = phonenum[i];
        }
    }
    clean_phonenum[j] = '\0';  // 문자열 종료 문자 추가

    // printf("저장되는 전화번호: %s\n", clean_phonenum);//확인용
    memcpy(new_phone_num,clean_phonenum,strlen(clean_phonenum)+1);
}

void masking_phonenum(member *a){
    for(int j = 0 ; j < MAX_MEMBERS ; j++){
        for(int i = 0; i <11 ; i++){
            if((i<=1)||(i >=7 && i <= 10)){ //0,1,7,8,9,10
                printf("%c",a[j].phone_num[i]);
            }
            else if(i == 2){
                printf("%c-",a[j].phone_num[i]);
            }
            else if(i == 6){
                printf("*-");
            }
            else if(i >=3 && i <=5){
                printf("*");
            }
        }
        printf("\n");
    }
}

void sign_up()
{
    char fullpath[200];

    //입력했을때.txt 에 맞는 값이라고 했을때 넣는
    FILE *fp = fopen("account.txt", "a");  // 파일이 없으면 생성, 있으면 이어쓰기 모드 a+이랑은 뭐가 다르지?
    if (fp == NULL) {
        printf("파일 열기에 실패했습니다.\n");
        exit(1);
    }
    
    printf("이름을 입력하세요(나가기>exit): ");
    getchar();
    scanf("%s", new_name);
    if(strcmp(new_name,"exit")==0){
        printf("메인화면으로 돌아갑니다.\n");
        return;
    }

    printf("나이를 입력하세요(나가기>0): ");
    scanf("%d", &new_age);
    if(new_age == 0){
        printf("메인화면으로 돌아갑니다.\n");
        return;
    }
    
    // CSV 형식으로 파일에 저장!
    printf("회원가입이 완료되었습니다! 메인화면으로 돌아갑니다.\n");
    fprintf(fp, "%s|%s|%s|%s|%d\n", new_id, new_password, new_name, new_phone_num, new_age);
    fclose(fp);

    snprintf(fullpath, sizeof(fullpath), "./server/%s", new_id);     //   <- server폴더는 미리 있어야 하며 여기 "임시"에 새로 만들어진 아이디를 넣으면 됨

    if (mkdir(fullpath, 0777) == -1){
        perror("폴더 생성 실패");
    }

    else{
    printf("%s 경로에 Directory 생성 완료\n", fullpath);               //  <-이거는 폴더 만들어졌다고 나오는 것
    }
}

void csv_to_struct_mem() { 
    FILE *file = fopen("account.txt","r");
    char line[255];
    int count = 0;

    while(fgets(line, sizeof(line),file) != NULL && count < MAX_MEMBERS){
        line[strcspn(line,"\r\n")] = 0;  //줄바꿈 문자 0으로 바꿔줌

        char *token = strtok(line,"|");  //,기준으로 나누어 가져오겟다 

        if(token == NULL) continue;
            strcpy(new_mem[count].id, token);
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[count].password, token);
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[count].name, token);
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[count].phone_num, token);
            token = strtok(NULL, "|");
            
        if (token == NULL) continue;
            new_mem[count].age = atoi(token);
            
        count++;
    }
    fclose(file);
    account_cnt = count;
    // for (int j = 0; j < count; j++) {
    //     printf("회원 %d: %s, %s, %s, %s, %d\n", j+1, new_mem[j].id, new_mem[j].password, new_mem[j].name,new_mem[j].phone_num,new_mem[j].age );
    // } 
}

int search_members_main(){
    int search_mem_choice;
    puts("회원을 검색합니다.");
    puts("1.  ID로 검색\n2.  이름으로 검색");
    printf(" > > > ");
    scanf("%d",&search_mem_choice);
    return search_mem_choice;
}

void search_mem_name(){
    // int search_mem_choice;없어도 될 듯?
    char search_name[50];
    member temp[MAX_MEMBERS]; //일치하는 결과를 일단 요기 담음 
    int found_count = 0; // 몇명 검색됐나요
    puts("이름으로 검색함!~");
    printf("검색할 이름 입력: ");
    getchar();
    scanf("%s",search_name);
    for(int i =1; i <=account_cnt; i++){  //카운트 수로 변경하기@
        if(strcmp(search_name,new_mem[i].name)==0){ //이름이 정확히 일치하면
            temp[found_count++] = new_mem[i]; //temp에 저장하고 카운트 1증가시킴 
        }
    }
        if(found_count == 0){
            printf("일치하는 회원정보가 없습니다.\n");
            return;
        }
        qsort(temp, found_count, sizeof(member),comfunc_by_member_id);
        //qsort(정렬할 배열, 배열 안에있는 실제 요소 개수, 요소의 크기, 비교함수<-아이디기준비교);
    if (found_count > 10){
        print_member_page(temp,found_count);
        return;
    }

        printf("총 %d명의 회원이 검색되었습니다.\n", found_count);  //몇건?
        for(int i = 0; i < found_count; i++){    
            printf("ID: %s\n",temp[i].name);
            printf("나이: %d\n",temp[i].age);
            printf("전화번호: ");
            masking_user_phonenum(temp,i);
        }
}

// id_account : 찾고자 하는 아이디 , found_account 찾은 유저 정보 구조체의 index
void retrieve_id_from_member(int* found_account, char id_account[]) {
    int cnt = 0;
    char *ptr;

    // 1. 부분 문자열이 포함된 회원 인덱스 찾기
    for (int i = 1; i < account_cnt; i++) {
        ptr = strstr(new_mem[i].id, id_account);
        if (ptr != NULL) {
            found_account[cnt++] = i;
        }
    }

    if (cnt == 0) {
        printf("일치하는 아이디가 없습니다.\n");
        return;
    }

    // 2. 찾은 회원을 별도의 구조체 배열에 복사
    member temp[MAX_MEMBERS];
    for (int i = 0; i < cnt; i++) {
        temp[i] = new_mem[found_account[i]];
    }

    // 3. 이름 기준 정렬
    qsort(temp, cnt, sizeof(member), comfunc_by_member_name);

    // 4. 정렬된 결과 출력
    if (cnt>10) {  //10개이상이면 페이징
        print_member_page(temp,cnt);
        return;
    }
    printf("총 %d개의 아이디를 찾았습니다. (이름순 정렬)\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("이름: %s\n", temp[i].name);
        printf("아이디: %s\n", temp[i].id);
        printf("전화번호: ");
        masking_user_phonenum(temp, i);
        printf("나이: %d\n\n", temp[i].age);
    }
}

void masking_user_phonenum(member *a, int login_index){
    for(int i = 0; i <11 ; i++){
        if((i==0)||(i==1)){ //0,1,7,8,9,10
            printf("%c",a[login_index].phone_num[i]);
        }
        else if(i == 2){
            printf("%c-",a[login_index].phone_num[i]);
        }
        else if(i >=3 && i <=5){
            printf("*");
        }
        else if(i == 6){
            printf("*-");
        }
        else if (i >=7 && i <= 10){
            printf("%c",a[login_index].phone_num[i]);
        }
    }
        printf("\n");
}

void admin_can_check_account_info(member *a)
{
    qsort(new_mem, account_cnt, sizeof(member), comfunc_by_member_name);

    member temp[MAX_MEMBERS];
    int cnt = 0;
    for (int i = 1; i < account_cnt; i++) { //관리자 0번이라 1로 시작합니다.
        temp[cnt++] = new_mem[i];
    }

    if (cnt > 10) {
        print_member_page(temp, cnt);
    } else {
        for (int i = 0; i < cnt; i++) {
            printf("이름: %s, ", temp[i].name);
            printf("아이디: %s, ", temp[i].id);
            printf("전화번호: ");
            masking_user_phonenum(temp, i);
            printf("나이: %d\n", temp[i].age);
        }
    }
}



/*멤버의 이름으로 정렬하기 위한 함수!*/
int comfunc_by_member_name(const void *a, const void *b)
{
    return strcmp(((member*)a)->name,((member*)b)->name);
}
//아이디 기준 정렬하기위한 함수
int comfunc_by_member_id(const void *a, const void *b) {
    return strcmp(((member*)a)->id, ((member*)b)->id);
}

/*admin_article.csv 파일을 원하는 인덱스를 삭제하는 함수*/
void delete_a_article_from_admin_articles(int del_index)
{
     // ./admin_article.csv 파일의 내용을 구조체 변수에 담는 함수
    // 호출후 admin_articles라는 구조체 배열에 모두 담는다.
    admin_articles_cnt=0;
    store_to_admin_article_struct(); 

    // 6번인덱스를 지우고싶다면 
    // 이건 삭제를 위한 인덱스 추후 삭제하고자 하는 인덱스를 입력받음
    

    //
    //삭제하는 내용!
    for(int i=del_index; i<admin_articles_cnt; i++)
    {
        admin_articles[i] = admin_articles[i+1];
    }
    //파일에 씁시다! 조심 w는 재앙이야!
    FILE *file = fopen("./admin_article.txt","w");
    if(file==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        
    }
    for(int i=0; i<admin_articles_cnt; i++)
    {

        // if(articles[i].article_id!=0)
        
        if(admin_articles[i].article_id!=0)
        {               
            fprintf(file, "%d|%s|%s|%s|%s|%d|%s|%d\n",
                admin_articles[i].article_id,
                admin_articles[i].article_title,
                admin_articles[i].article_content,
                admin_articles[i].writer_id,
                admin_articles[i].reciever_id,
                admin_articles[i].write_time_1,
                admin_articles[i].write_time_2, 
                admin_articles[i].read_count );
        }
        
    }

    fclose(file);
}

void delete_a_article_from_articles(int del_index)
{
     // ./article.txt 파일의 내용을 구조체 변수에 담는 함수
    // 호출후 articles라는 구조체 배열에 모두 담는다.
    articles_cnt=0;
    store_to_article_struct(); 

    // 6번인덱스를 지우고싶다면 
    // 이건 삭제를 위한 인덱스 추후 삭제하고자 하는 인덱스를 입력받음
    
    //
    //삭제하는 내용!
    for(int i=del_index-1; i<articles_cnt; i++)
    {
        articles[i] = articles[i+1];
    }

    // printf(" 글의 갯수를 몇개로 파악하느뇨? %d\n", articles_cnt);

    for(int i=0; i<articles_cnt; i++)
    {
        printf("id: %d ,content : %s\n",articles[i].article_id,articles[i].article_content);
    }

    //파일에 씁시다! 조심 w는 재앙이야!
    FILE *file = fopen("./article.txt","w");
    if(file==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        
    }

    for(int i=0; i<articles_cnt; i++)
    {
        if(articles[i].article_id!=0)
        {
            fprintf(file, "%d|%s|%s|%s|%s|%d|%s|%d\n",
                articles[i].article_id, 
                articles[i].article_title,
                articles[i].article_content,
                articles[i].writer_id,
                articles[i].reciever_id,
                articles[i].write_time_1,
                articles[i].write_time_2, 
                articles[i].read_count
            );
        } 

                
    }

    fclose(file);
}

void store_to_admin_article_struct()
{
    admin_articles_cnt=0;
    FILE *file = fopen("./admin_article.txt","r");
    
    // 구조체 배열을 0으로 초기화한다! - 사용중인 배열의 마지막을 찾기위한 초기화
    memset(&admin_articles,0,sizeof(admin_articles));


    char line[256];// 한줄을 저장할 배열

    if(file==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        
    }
    //50개의 구조체 배열을 생성했다. 삭제를 위한! 
    
    int row_count=0;    
    //reading by line
    while(fgets(line, sizeof(line),file))
    {

        char *token = strtok(line,"|");
        
        int field_count =0;
        //reading by column(쉼표를 이용한 필드 )
        while(token !=NULL)
        {
           //글 id
            if(field_count==0)
           {
            int article_id = atoi(token);
            if(article_id!=0)            
                // printf("%d\t", article_id); //각 필드를 출력
                //구조체에 넣자!
                admin_articles[row_count].article_id = article_id;       
           }
           //글제목
           else if(field_count==1)
           {
            char title[50];
            //파일 토큰에서 글제목을 가져와서
            strcpy(title,token);
            // 구조체 아티클[행번호].글제목으로 넣는다!
            strcpy(admin_articles[row_count].article_title, title);       

           }
           //글 컨텐츠
           else if(field_count==2)
           {
            char content[50];
            //파일 토큰에서 글내용을 가져와서
            strcpy(content,token);
            // 구조체 아티클[행번호].글내용으로 넣는다!
            strcpy(admin_articles[row_count].article_content, content);       

            // printf("글내용 :%s\t", content); //각 필드를 출력
           }
            // 글작성자 아이디
           else if(field_count==3)
           {
            char writer[50];
            // 파일 토큰에서 작성자를 가져와서
            strcpy(writer,token);
            // 구조체 아티클[행번호].작성자로 넣는다.!  - admin이기대문에 "0"을 고정으로 넣는게 어떨까?
            strcpy(admin_articles[row_count].writer_id, writer);
            // printf("작성자입니다 %s\t", writer); //각 필드를 출력
           }
           else if(field_count==4)
           {
            //받는이가 없는 경우도 있습니다 기본값이 0입니다.
            char reciever[50];
            // 파일 토큰에서 작성자를 가져와서
            strcpy(reciever,token);
            // 구조체 아티클[행번호].작성자로 넣는다.!  사실상 필요없는 필드이다. 왜냐? 어드민이 쓰는건 모두 공지
            strcpy(admin_articles[row_count].reciever_id, reciever);
           }
           else if(field_count==5)
           {
            //정렬을 위한 초로 이뤄진 시간 정보
            int write_time;
            write_time=atoi(token);
            admin_articles[row_count].write_time_1 = write_time;
            
           }

           else if(field_count==6)
           {
            //시간_2 (문자열 )
            
            char time_[50];
            strcpy(admin_articles[row_count].write_time_2 ,token);
            
           }
           else if(field_count==7)
           {
            //조회수
            int read_count;            
            read_count=atoi(token);
            admin_articles[row_count].read_count = read_count;
           }
            token = strtok(NULL, "|"); //다음 필드로 이동
            field_count++;
                        
        }
        row_count++;
        printf("\n");
        admin_articles_cnt++; //전역 
    }
    fclose(file);


}

void store_to_article_struct()
{

    FILE *file = fopen("./article.txt","r");
    
    // 구조체 배열을 0으로 초기화한다! - 사용중인 배열의 마지막을 찾기위한 초기화
    memset(&articles,0,sizeof(articles));


    char line[256];// 한줄을 저장할 배열

    if(file==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        
    }
    //50개의 구조체 배열을 생성했다. 삭제를 위한! 
    
    int row_count=0;    
    //reading by line
    while(fgets(line, sizeof(line),file))
    {

        char *token = strtok(line,"|");
        
        int field_count =0;
        //reading by column(쉼표를 이용한 필드 )
        while(token !=NULL)
        {
           //글 id
            if(field_count==0)
           {
            int article_id = atoi(token);
            if(article_id!=0)            
                // printf("%d\t", article_id); //각 필드를 출력
                //구조체에 넣자!
                articles[row_count].article_id = article_id;       
           }
           //글제목
           else if(field_count==1)
           {
            char title[50];
            //파일 토큰에서 글제목을 가져와서
            strcpy(title,token);
            // 구조체 아티클[행번호].글제목으로 넣는다!
            strcpy(articles[row_count].article_title, title);       

           }
           //글 컨텐츠
           else if(field_count==2)
           {
            char content[50];
            //파일 토큰에서 글내용을 가져와서
            strcpy(content,token);
            // 구조체 아티클[행번호].글내용으로 넣는다!
            strcpy(articles[row_count].article_content, content);       

            // printf("글내용 :%s\t", content); //각 필드를 출력
           }
            // 글작성자 아이디
           else if(field_count==3)
           {
            char writer[50];
            // 파일 토큰에서 작성자를 가져와서
            strcpy(writer,token);
            // 구조체 아티클[행번호].작성자로 넣는다.!
            strcpy(articles[row_count].writer_id, writer);
            // printf("작성자입니다 %s\t", writer); //각 필드를 출력
           }
           else if(field_count==4)
           {
            //받는이가 없는 경우도 있습니다 기본값이 0입니다.
            char reciever[50];
            // 파일 토큰에서 작성자를 가져와서
            strcpy(reciever,token);
            // 구조체 아티클[행번호].작성자로 넣는다.!
            strcpy(articles[row_count].reciever_id, reciever);
           }
           else if(field_count==5)
           {
            //시간_1 (int ) 정렬하기위해 존재
            int write_time;
            write_time=atoi(token);
            articles[row_count].write_time_1 = write_time;
            
           }

           else if(field_count==6)
           {
            //시간_2 (문자열 )
            
            char time_[50];
            strcpy(articles[row_count].write_time_2 ,token);
            
           }
           else if(field_count==7)
           {
            //조회수
            int read_count;            
            read_count=atoi(token);
            articles[row_count].read_count = read_count;
           }
            token = strtok(NULL, "|"); //다음 필드로 이동
            field_count++;                        
        }
        row_count++;
        printf("\n");
        articles_cnt++; //전역 
    }
    fclose(file);

}

void write_a_admin_article()
{
    
    // 디렉토리 유무 확인
    // 없으면 생성

    /* 해당 id/id_         
    getTotalLine("./admin_article.txt");   
    함수를통해 공지번호를 가져와서 문자열로 바꾸고 strcat으로 파일명 생성 

    */   

    FILE *file = fopen("./admin_article.txt","a");

    if(file ==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        exit(1);
    }  

    char user_id[50] = "admin";
    // char sender_id[3]= " ";  //없으면 공백으로 쓰자
    char receiver_id[50] =" ";
    time_t seconds;
    time(&seconds);

    article a;
    a = get_input_for_write_article();
    a.article_id = getTotalLine("./admin_article.txt");   // 이러면 해당 파일의 총행의 갯수를 가져옴
    strcpy(a.writer_id, user_id);
    strcpy(a.reciever_id, receiver_id);
    a.write_time_1 = seconds;
    /*시간을 문자열로 변환하기위한 작업
    */
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[100];
    sprintf(time_str, "%d년 %d월 %d일 %d시 %d분 %d초",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    
    strcpy(a.write_time_2, time_str);
    // a.write_time_2 =
    a.read_count = 0;
   
    /** 글번호 / 글제목/ 컨텐츠/ 글작성자/ 받는분/ 작성시간  <<-- 입력을 받아서 글등록하도록 변경 예정 */  
    // fprintf(file, "16,돼지고기를 먹는방법, 언제든먹을수 있지, %s, ,%d, \n", user_id, seconds);  
    fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d",
        a.article_id,
        a.article_title,
        a.article_content,
        a.writer_id,
        receiver_id,
        a.write_time_1,
        a.write_time_2 ,
        a.read_count
       );

    fclose(file);

    /**여기서부턴 각각 디렉토리에 배달! */
    csv_to_struct_mem();
    char folder_path[100];
    char file_path[100];
    char title[100], content[500];    
    int post_number = getTotalLine("./admin_article.txt"); 
    
    for(int i=0; i<account_cnt; i++)
    {
        
        
         // 1. 유저 폴더 경로 만들기
        snprintf(folder_path, sizeof(folder_path), "./server/%s", new_mem[i].id);

        do_mkdir(folder_path,0755); //디렉토리생성

        DIR *dir = opendir(folder_path);
        if(dir==NULL)
        {
            perror("폴더 열기 실패");
            printf("debug!%s",folder_path);
            exit(1);
        }       

        closedir(dir);
        snprintf(file_path, sizeof(file_path), "%s/%s_%d.txt", folder_path, "admin", post_number);

        FILE *fp = fopen(file_path, "w");
        if(fp== NULL)
        {
            perror("파일 저장 실패");
            return ;
        }
        fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d",
            a.article_id,
            a.article_title,
            a.article_content,
            a.writer_id,
            receiver_id,
            a.write_time_1,
            a.write_time_2 ,
            a.read_count
           );

        fclose(fp);
    }



}

article get_input_for_write_article()
{
    article a;
    char title[50];
    char content[500];
    getchar();
    

    printf("글 제목을 입력해주세요\n");
    scanf("%[^\n]", title);
    getchar();
    printf("글 내용을 입력해주세요\n");
    scanf("%[^\n]", content);

    // printf("%s\t%s", title, content);
    strcpy(a.article_title, title);
    strcpy(a.article_content, content);
    return a;
}

void show_article_list()
{

    FILE *file = fopen("./article.txt","r");
    
    
    char line[256];// 한줄을 저장할 배열

    if(file==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        
    }

    //reading by line
    while(fgets(line, sizeof(line),file))
    {
        char *token = strtok(line,"|");
        int field_count =0;
        //reading by column(쉼표를 이용한 필드 )
        while(token !=NULL)
        {
           //id
            if(field_count==0)
           {
            int article_id = atoi(token);
            if(article_id!=0)            
                printf("%d\t", article_id); //각 필드를 출력

           }
           else if(field_count==1)
           {
            char title[50];
            strcpy(title,token);
            printf("%s\t", title); //각 필드를 출력
           }
           else if(field_count==2)
           {
            char content[500];
            strcpy(content,token);
            printf("%s\t", content); //각 필드를 출력
           }
           else if(field_count==3)
           {
            char writer[50];
            strcpy(writer,token);
            // printf("%s\t", writer); //각 필드를 출력
           }
           else if(field_count==4)
           {
            char receiver[50];
            strcpy(receiver,token);
            // printf("%s\t", receiver); //각 필드를 출력
           }
           else if(field_count==5)
           {
            char time_[50];
            strcpy(time_, token);
            
           
            printf("ctime의 결과%s\n", time_);

            // printf("timeinfo : %d년 %d월 %d일 %d시 %d분 %d초\n", year,month, day,hour, min, sec);

           }

            token = strtok(NULL, "|"); //다음 필드로 이동
            field_count++;
            //타이틀만 나오게 하려면 어떻게 해야할까?
            
        }
        printf("\n");
    }

    fclose(file);
    

}

void show_my_info(int login_index){
    puts("내정보 보기");
    printf("이름: %s\n", new_mem[login_index].name);
    printf("아이디: %s\n", new_mem[login_index].id);
    printf("전화번호: %s\n ",new_mem[login_index].phone_num);
    
    printf("나이: %d\n",new_mem[login_index].age);
}

void show_paging()
{
    char input_key;

    int ends;
    
    int starts=0;
    ends = starts+10;
    // show_main_page();

    store_to_article_struct();
    // 구조체 배열의 포인터를 만들고 거기에 쓰라고 명령한다면?
    article au[100];
    article user_articles_rv[50]; 
    int total_cnt=0;
    int rec_cnt=0;
    
    /* user_id가 N7h80y 이런 애들만 가져오겠다! */

    memset(&user_articles_rv,0,sizeof(user_articles_rv));
    // store_to_receiver_article_struct("N7h80y", user_articles_rv);  

    do{
        system("clear");
        
        for (int i=starts; i< ends; i++)
        {   
            if(user_articles_rv[i].article_id!=0)
            {
                printf("글내용 %s   작성시간%s\n",user_articles_rv[i].article_title,user_articles_rv[i].write_time_2);
            }
            
        }

        printf("이전b  다음n \n");
        getchar();
        scanf("%c", &input_key);
        
        if(input_key=='b'){
            if(starts >= 0){                
                getchar();
                starts-=10;
            }
        }
        else if(input_key=='n'){
            getchar();
            starts+=10;
        }
    } while(input_key !='q');   
}

int log_out_or_exit(){
    int log_out = 0;
    printf("======= 나가기 ======= \n");
    printf("1. 로그아웃\n");
    printf("2. 종료\n");
    scanf("%d",&log_out);
    return log_out;
}

void admin_main(){
    char admin_menu_choice ;
    
    while(1){
        printf("===========[ 관리자용 ]===========\n");
        printf("t.텍스트보내기\n");
        printf("f.유저확인\n");
        printf("z.종료\n");
        printf("─────────────────\n");
        printf("선택 >> ");

        getchar();//버퍼를 먼저 비우기
        scanf(" %c",&admin_menu_choice);
    

        if(admin_menu_choice == 't'){  //텍스트보내기
            printf("[ 텍스트 보내기 ]\n");
            write_a_admin_article();
        }
        else if(admin_menu_choice == 'f'){ //유저확인
            printf("[ 유저확인 ]\n");
            admin_can_check_account_info(new_mem);
        }
        else if(admin_menu_choice == 'z'){ //종료하기
            log_out_or_exit();
            break;
        }
        else{
            printf("다시 입력하세요.\n");
        }
        break;
    }
}

void print_member_page(member *arr, int total_count) {
    int start = 0;
    char key;

    while (1) {
        system("clear");
        printf("검색 결과 (총 %d명)\n\n", total_count);

        // 10명씩 출력
        for (int i = start; i < start + 10 && i < total_count; i++) {
            printf("이름: %s\n", arr[i].name);
            printf("아이디: %s\n", arr[i].id);
            printf("전화번호: ");
            masking_user_phonenum(arr, i);
            printf("나이: %d\n\n", arr[i].age);
        }

        printf("q. 이전 | r. 다음 | x. 종료 >> ");
        getchar();  // 버퍼 제거
        scanf("%c", &key);

        if (key == 'q' && start >= 10) start -= 10;
        else if (key == 'r' && start + 10 < total_count) start += 10;
        else if (key == 'x') break;
    }
}


void write_user_article_with_number(const char *user_id) {
    char folder_path[100];
    char file_path[100];
    char title[100], content[500];
    int post_number = 1;

    // 1. 유저 폴더 경로 만들기
    snprintf(folder_path, sizeof(folder_path), "./server/%s", user_id);

    // 2. 폴더 열고 유저 글 파일 개수 세기
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        perror("폴더 열기 실패");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // 글 파일명: user_id_숫자.txt
        if (strncmp(entry->d_name, user_id, strlen(user_id)) == 0) {
            post_number++;
        }
    }
    closedir(dir);

    // 3. 새 글 파일 경로 만들기
    snprintf(file_path, sizeof(file_path), "%s/%s_%d.txt", folder_path, user_id, post_number);

    // 4. 제목/내용 입력
    printf("글 제목 입력: ");
    getchar();
    scanf("%[^\n]", title);
    getchar();
    printf("글 내용 입력: ");
    scanf("%[^\n]", content);
    getchar();

    // 5. 파일에 저장
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        perror("파일 저장 실패");
        return;
    }

    // 작성 시간 추가
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[100];
    sprintf(time_str, "%d년 %d월 %d일 %d시 %d분 %d초",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    fprintf(fp, "== %s ==\n제목: %s\n내용: %s\n", time_str, title, content);
    fclose(fp);
    printf("글이 [%s]에 저장되었습니다!\n", file_path);
    /*여기까지가 서현님 작성 코드*/

    


    /*여기부터가 내가 작성코드 */
    FILE *file = fopen("./server/article.txt","a");

    if(file ==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        exit(1);
    }

    time_t seconds;
    time(&seconds);

    article a;    
    a.article_id = post_number;   
    strcpy(a.writer_id, user_id);
    strcpy(a.reciever_id, " ");
    strcpy(a.article_title,title);
    strcpy(a.article_content, content);
    a.write_time_1 = seconds;
    /*시간을 문자열로 변환하기위한 작업
    */   
    strcpy(a.write_time_2, time_str);
    // a.write_time_2 =
    a.read_count = 0;
    strcpy(a.file_address,file_path);

    fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d|%s\n",
         a.article_id,
         a.article_title,
         a.article_content,
         a.writer_id,
         a.reciever_id,
         a.write_time_1,
         a.write_time_2 ,
         a.read_count,
         a.file_address
        );
    fclose(file);

}

/* 텍스트 라인 가져오는 함수*/
int getTotalLine(char *name)
{
    FILE *fp;

    int line =0;
    char c;
    fp=fopen(name,"r");
    while((c=fgetc(fp))!=EOF)
    {
        if(c=='\n')
        {
            line++;
        }

    }
    fclose(fp);
    return(line);
}

/* 4/8추가함 디렉토리생성 함수 */
int do_mkdir(const char *pasPathName, mode_t mode) 
{
    int nStatus = 0;
    struct stat st;

    if (stat(pasPathName, &st) != 0) 
    {
        if (0 != mkdir(pasPathName, mode) && EEXIST != errno) 
        {
            nStatus = -1;
        }
    }
    else if (!S_ISDIR(st.st_mode)) 
    {
        nStatus = -1;
    }
	
    return(nStatus);
}
