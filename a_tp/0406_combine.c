#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct_member.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#define MAX_MEMBERS 100




char new_id [40];
char new_password[20];
char new_name[20];
int new_age;
char new_phone_num[40];

int articles_cnt;
int members_cnt;
int account_cnt;
int admin_articles_cnt;

int write_idx =0 ;

member new_mem[MAX_MEMBERS]; 
article articles[1000];
article admin_articles[300]; 

void show_paging();
void show_main_page();
void print_main_menu();  //메인메뉴 프린트
int login(member *a);   // 로그인하는 함수
void main_menu2(int login_index);  //로그인 후 메인메뉴 프린트
void check_password();  // 비밀번호 확인 함수
void save_phonenum();  //휴대폰번호 양식에 맞게 저장하는 함수
void masking_phonenum(member *a);  //휴대폰 번호 가운데 마스킹하는 함수
void sign_up();  //회원가입(조건 맞을 때 csv파일 추가)
void csv_to_struct_mem(); // 회원csv 파일 -> 구조체 new_mem 파일에 담는 함수
void search_mem();  // 회원정보 조회하는 함수
void write_a_article();
void admin_can_check_account_info();

void order_by_account_name();  //멤버이름으로 정렬하기 위한 함수
int comfunc_by_member_name(const void *a, const void *b);

void delete_a_article_from_admin_articles(int del_index);

void  retrieve_id_from_member(int* found_account, char id_account[]);

void store_to_writer_article_struct(char *user_id,  article* user_articles);
// int * store_to_receiver_article_struct(char *user_id,  article* user_articles);
int * store_to_receiver_article_struct(char *user_id,  int* rv, int* wr);

void store_to_admin_article_struct();

void store_to_article_struct();

void write_a_admin_article();

article get_input_for_write_article();


void show_article_list(char *login_id);


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

void show_main_page()
{
    char input_key;
    int starts=0;
    int ends;
        
    do{
        system("clear");
        show_paging(starts);

        printf("이전b  다음n \n");
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


int main(){   
   
    // show_paging();
// 
store_to_article_struct();
// write_a_article();
char user_id[50]="kVu7ty";
int rv[100]={0,};

int wr[100]={0,};

article user_articles[500];

store_to_receiver_article_struct(user_id, rv, wr);
int rv_cnt=0;
for(int i=0; i<30; i++)
{
    if(rv[i]!=0)
    {
        int index_;
        index_ = rv[i];
        printf("index:%d  제목 %s 내용 %s\n",articles[index_].article_id,articles[index_].article_title, articles[index_].article_content);    
        // printf("%d(%d) %s\n",i+1,user_articles[i].article_id, user_articles[i].article_title);
        rv_cnt++;
    }
    
}
printf("총 %d개의 메시지가 있습니다.\n",rv_cnt);
int wr_cnt=0;
for(int i=0; i<30; i++)
{
    if(wr[i]!=0)
    {
        int index_;
        index_ = wr[i];
        printf("index:%d  제목 %s 내용 %s\n",articles[index_].article_id,articles[index_].article_title, articles[index_].article_content);    
        wr_cnt++;
    }   
  
}
printf("총 %d개의 메시지가 있습니다.\n",wr_cnt);

int index_num;
printf("보내고자 하는 아이템을 괄호에 있는 숫자를 입력(index_num)");
scanf("%d", &index_num);

}


void print_main_menu(){
    int main_menu_choice;
    puts(" ~ 신난다 ~ 재미나다 ! ~ 우리들의 버디버디 ~ ");
    puts("---------------- LOG IN -------------------");
    puts("1:\t\t로그인");
    puts("2:\t\t회원가입");
    printf(" >>> ");
    scanf("%d",&main_menu_choice);
}

void main_menu2(int login_index) {
    char choice;
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
        scanf(" %c", &choice);

        switch (choice) {
            case 'w':
                // write_a_article(login_id);  // 유저 ID 넘기기
                break;
            case 'a':
                show_article_list(login_id);
                break;
            case 't':
                // send_text(login_id);
                break;
            case 'f':
                search_mem();  // 기존 함수 사용
                break;
            case 'c':
                // show_my_info(login_index);  // 구조체 배열 인덱스 넘김
                break;
            case 'z':
                printf("로그아웃합니다.\n");
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}



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

void write_a_article()
{
    // 디렉토리 생성하기 체크해서 있으면 무시
    // user_id[10] ="kVu7ty";
    
    char user_id[50] = "0";
    // char sender_id[3]= " ";  //없으면 공백으로 쓰자
    char receiver_id[50];
    time_t seconds;
    time(&seconds);

    int choice_sendornot[10];
    printf("글을 보내시겠습니까 1. 보내기 2. 임시저장하기");
    scanf("%d",&choice_sendornot);

    if(choice_sendornot==1)
    {
        //보내기이므로 상대 아이디를 입력받는다.receiver_id
        
        printf("받는 사람 id를 입력해주세요");
        scanf("%s",&receiver_id);

        int ret[10];
        retrieve_id_from_member(ret, receiver_id);
        

    }
    char * curr_dir = getcwd(NULL, 0);
    if(curr_dir ==NULL)
    {
        fprintf(stderr, "Error: getcwd() cannot execute\n");
        exit(1);
    }

    strcat(receiver_id,"scar");
    char destination[50];
    strcpy(destination, "./server/");
    strcat(destination, receiver_id);
    
    //receiver_id가 있다고 가정하고 계속 작성
    do_mkdir(destination, 0755); //server/id로 디렉터리 생성
    char s1[10];
    sprintf(s1, "%d",write_idx);
    strcat(destination, s1);
    strcat(destination,".txt");
    FILE *fp = fopen(destination, "w");  
    printf("디버깅 %s",destination);
    if (fp == NULL) {
        printf("파일 열기에 실패했습니다.\n");
        exit(1);
    }


    char title[50];
    char content[500];

    printf("글 제목을 입력해주세요\n");
    scanf("%[^\n]", title);
    getchar();
    printf("글 내용을 입력해주세요\n");
    scanf("%[^\n]", content);


    article a;
    // printf("%s\t%s", title, content);
    strcpy(a.article_title, title);
    strcpy(a.article_content, content);

    
    strcpy(a.writer_id, user_id);
    strcpy(a.reciever_id, receiver_id);
    a.write_time_1 = seconds;
    /*시간을 문자열로 변환하기위한 작업
    */
    char char_time[100];
    struct tm* pTimeInfo;
    pTimeInfo = localtime(&seconds);
    int year = pTimeInfo->tm_year +1900;
    int month = pTimeInfo->tm_mon+1;
    int day = pTimeInfo->tm_mday;
    int hour = pTimeInfo->tm_hour;
    int min = pTimeInfo->tm_min;
    int sec = pTimeInfo->tm_sec;
    sprintf(char_time,"%d년 %d월 %d일 %d시 %d분 %d초",year,month,day,hour, min,sec);
    strcpy(a.write_time_2, char_time);
    // a.write_time_2 =
    a.read_count = 0;
   
    /** 글번호 / 글제목/ 컨텐츠/ 글작성자/ 받는분/ 작성시간  <<-- 입력을 받아서 글등록하도록 변경 예정 */  
    // fprintf(file, "16,돼지고기를 먹는방법, 언제든먹을수 있지, %s, ,%d, \n", user_id, seconds); 
    // "%d|%s|%s|%s|%s|%d|%s|%d\n" 
    fprintf(fp ,"%d|%s|%s|%s|%s|%d|%s|%d\n",
         a.article_id,
         a.article_title,
         a.article_content,
         a.writer_id,
         receiver_id,
         a.write_time_1,
         a.write_time_2 ,
         a.read_count
        );
    write_idx++;
    fclose(fp);
}


int login(member *a){
    char login_id[50];
    char login_pw[50];
    int flag_id = 0;
    int user_num = 0;

    while(1){
        puts("ID: ");
        scanf("%s",login_id);

        for(int i = 0; i < 10; i++){
            if (strcmp(login_id,a[i].id)==0){
                flag_id = 1;
                user_num = i;
            }
        }
        if(flag_id != 1){
            printf("없는 아이디 입니다.");   //언니는 내일 여기 들어가면 되는거겟지? 잘 할 수 잇지? ^^*
            continue;
        }
        puts("PASSWORD: ");
        scanf("%s",login_pw);
        
        if(strcmp(login_pw,a[user_num].password)==0){
            printf("로그인 성공: %s님, 안녕하세요!\n",a[user_num].name);
            break;
        }
        else{
            printf("비밀번호가 일치하지 않습니다. 다시 입력하세요\n");
            continue;
        }
        return user_num;
    }
}

void check_password(){
    int lower_, upper_,digit_, spec_; // 소문자, 대문자, 숫자
    char password[20]; // 비밀번호 입력하는 배열이구요
    int special[20] = {0}; // 특수문자배열. 문자를 "숫자화" 하여 아스키로 인식하게 하는 배열
    int korean_ = 0;  //한글 확인할때
    char check_pw[20] = {0};  //비밀번호 확인할때

    while(1){
        printf("비밀번호를 입력하세요: ");
        scanf("%s",password);
        lower_= upper_ = digit_ = spec_ =0; //초기화

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
                scanf("%s",check_pw);
            
                if(strcmp(password,check_pw) == 0){
                    printf("비밀번호가 일치합니다.\n");
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

    new_password[40] = password[20];
}

void save_phonenum() {
    char phonenum[40];
    char clean_phonenum[40];
    int j = 0;  //clean_phonenum에 접근하기위한 인덱스

    puts("전화번호 입력: ");
    scanf("%s", phonenum);  // 전화번호 입력 받기

    // 원래 문자열 돌면서 '-'가 아니면 클린넘버에 넣기
    for (int i = 0; i < strlen(phonenum); i++) {
        if (phonenum[i] != '-') {
            clean_phonenum[j++] = phonenum[i];
        }
    }
    clean_phonenum[j] = '\0';  // 문자열 종료 문자 추가

    printf("저장되는 전화번호: %s\n", clean_phonenum);//확인용
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

    //입력했을때.txt 에 맞는 값이라고 했을때 넣는
    FILE *fp = fopen("account.txt", "a");  // 파일이 없으면 생성, 있으면 이어쓰기 모드 a+이랑은 뭐가 다르지?
    if (fp == NULL) {
        printf("파일 열기에 실패했습니다.\n");
        exit(1);
    }
    
    // 사용자로부터 입력 받기 (조건을 추가해야겠지요)
    printf("아이디: ");
    scanf("%s", new_id);
    printf("비밀번호: ");
    scanf("%s", new_password);
    printf("이름: ");
    scanf("%s", new_name);
    printf("나이: ");
    scanf("%d", &new_age);
    printf("전화번호: ");
    scanf("%s", new_phone_num);
    
    // CSV 형식으로 파일에 저장!
    fprintf(fp, "%s|%s|%s|%d|%s\n", new_id, new_password, new_name, new_age, new_phone_num);
    fclose(fp);
    csv_to_struct_mem(new_mem);
    search_mem(new_mem);
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

    for (int j = 0; j < count; j++) {
        printf("회원 %d: %s, %s, %s, %s, %d\n", j+1, new_mem[j].id, new_mem[j].password, new_mem[j].name,new_mem[j].phone_num,new_mem[j].age );
    }
}

void search_mem(){
    csv_to_struct_mem(new_mem);
    int search_mem_choice;
    char search_name[50];
    char all_mem_name [MAX_MEMBERS] ={0};

    printf("회원검색합니다~ \nID로 찾기: 1\n이름으로 찾기: 2\n >>> ");
    scanf("%d",&search_mem_choice);


    if(search_mem_choice == 2){
        puts("이름으로 검색함!~");
        printf("검색할 이름 입력: ");
        scanf("%s",search_name);
        printf("입력한 이름: %s\n",search_name);

        for(int i =0; i <11; i++){  //카운트 수로 변경하기@
            if(strcmp(search_name,new_mem[i].name)==0){
                printf("일치하는 회원정보가 있습니다.\n");  //몇건?
                printf("ID: %s, 나이: %d, 전화번호: %s",new_mem[i].id,new_mem[i].age,new_mem[i].phone_num);
            }
        }
    }
        
}

void admin_can_check_account_info()
{

     
    //관리자는 유저의 비밀번호를 제외한 모든 내용을 열람할수 있어야 한다. 
    // 1. 유저의 모든 정보를 가져오는 new_mem을 가져온다
    // 2. 거기서 password를 제외한 모든 내용을 출력한다.
    csv_to_struct_mem();     //account_cnt , new_mem 

    for(int i=0; i<account_cnt;i++ )
    {
        printf("유저의 아이디 : %s \n",new_mem[i].id);
        printf("유저의 이름 : %s \n",new_mem[i].name);
        printf("유저의 전화번호 : %s \n",new_mem[i].phone_num);
        printf("유저의 나이 : %d \n",new_mem[i].age);        
    }
}

void order_by_account_name()
{
    /*account가 총 몇명인지 account_cnt를 갱신하기 위해 호출하는 함수*/
    csv_to_struct_mem();    

    // 정렬전
    printf("정렬전입니다!");
    for(int i=0; i<account_cnt; i++)
    {

        printf("유저의 이름 %s\n", new_mem[i].name);
    }
    
    printf("\n");

    // magic here
    qsort((member*) new_mem, account_cnt, sizeof(member),comfunc_by_member_name);
    
    // 아이디로 정렬후
    for(int i=0; i<account_cnt; i++)
    {

        printf("유저의 이름 %s\n", new_mem[i].name);
    }
}



/*멤버의 이름으로 정렬하기 위한 함수!*/
int comfunc_by_member_name(const void *a, const void *b)
{
    return strcmp(((member*)a)->name,((member*)b)->name);
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

// id_account : 찾고자 하는 아이디 , found_account 찾은 유저 정보 구조체의 index
void  retrieve_id_from_member(int* found_account, char id_account[])
{
    
    int cnt=0;
    csv_to_struct_mem(); // csv-> 구조체 담는 함수
    char *ptr;
        // account_cnt 는 전역변수를 씁니다.
        for(int i=0; i<account_cnt;i++)
        {            
            ptr = strstr(new_mem[i].id,id_account);
            if(ptr!=NULL)
            {   // aj << alreadyjoined 라는 구조체 배열에 넣고싶었으나 원하는대로 동작이 안됨 할수없이 인트배열에 넣음
                found_account[cnt]=i;
                cnt++;
            }
        }  
        // testcode
        for(int i=0; i<cnt;i++)
        {   
            int index_ =found_account[i];
            printf("%d\n",index_);
            printf(" 찾은놈 아이디 : %s\n",  new_mem[index_].id);
        }
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
        int article_id;
        int field_count =0;
        //reading by column(쉼표를 이용한 필드 )
        while(token !=NULL)
        {
           //글 id
            if(field_count==0)
           {
            article_id = atoi(token);
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
            // printf("test930라인  %s %d\n", content, article_id);
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
        
        articles_cnt++; //전역 
    }
    fclose(file);

}

// void write_a_admin_article()
// {
    


//     // 입력을 받는 함수/  사용자로부터 입력받는 필드 글제목, 컨텐츠
    

//     // 받은 입력을 구조체에 넣는 함수/ 입력외에 들어가는 정보들 article 마지막id, user_id, time_t

//     char user_id[50] = "0";
//     // char sender_id[3]= " ";  //없으면 공백으로 쓰자
//     char receiver_id[50]="scar";
//     time_t seconds;
//     time(&seconds);

//     int choice_sendornot[10];
//     printf("글을 보내시겠습니까 1. 보내기 2. 임시저장하기");
//     scanf("%d",&choice_sendornot);

//     if(choice_sendornot==1)
//     {
//         //보내기이므로 상대 아이디를 입력받는다.receiver_id
        
//         printf("받는 사람 id를 입력해주세요");
//         scanf("%s",&receiver_id);

//         // id_account : 찾고자 하는 아이디 , found_account 찾은 유저 정보 구조체의 index
//         // void  retrieve_id_from_member(int* found_account, char id_account[])
//         int ret[10];
        
//         retrieve_id_from_member(&ret , receiver_id);

//     }
//     char destination[50];
//     strcpy(destination, "./server/");
//     strcat(destination, receiver_id);
//     //receiver_id가 있다고 가정하고 계속 작성
//     do_mkdir(destination, 0755); //server/id로 디렉터리 생성

  
//     char title[50];
//     char content[500];

//     printf("글 제목을 입력해주세요\n");
//     scanf("%[^\n]", title);
//     getchar();
//     printf("글 내용을 입력해주세요\n");
//     scanf("%[^\n]", content);


//     article a;
//     // printf("%s\t%s", title, content);
//     strcpy(a.article_title, title);
//     strcpy(a.article_content, content);

//     a.article_id = 17;   
//     strcpy(a.writer_id, user_id);
//     strcpy(a.reciever_id, receiver_id);
//     a.write_time_1 = seconds;
//     /*시간을 문자열로 변환하기위한 작업
//     */
//     char char_time[100];
//     struct tm* pTimeInfo;
//     pTimeInfo = localtime(&seconds);
//     int year = pTimeInfo->tm_year +1900;
//     int month = pTimeInfo->tm_mon+1;
//     int day = pTimeInfo->tm_mday;
//     int hour = pTimeInfo->tm_hour;
//     int min = pTimeInfo->tm_min;
//     int sec = pTimeInfo->tm_sec;
//     sprintf(char_time,"%d년 %d월 %d일 %d시 %d분 %d초",year,month,day,hour, min,sec);
//     strcpy(a.write_time_2, char_time);
//     // a.write_time_2 =
//     a.read_count = 0;
   
//     /** 글번호 / 글제목/ 컨텐츠/ 글작성자/ 받는분/ 작성시간  <<-- 입력을 받아서 글등록하도록 변경 예정 */  
//     // fprintf(file, "16,돼지고기를 먹는방법, 언제든먹을수 있지, %s, ,%d, \n", user_id, seconds);  
//     fprintf(fp ,"%d|%s|%s|%s|%s|%d|%s|%d\n\n",
//         a.article_id,
//         a.article_title,
//         a.article_content,
//         a.writer_id,
//         receiver_id,
//         a.write_time_1,
//         a.write_time_2 ,
//         a.read_count
//        );

//     fclose(file);
// }


void show_article_list(char *login_id)
{
    char user_id[30];

    strcpy(user_id,login_id);

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
            
           
            // printf("ctime의 결과%s\n", time_);

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

/**유저 아이디를 받아서 작성자 == user_id인 내용 구조체에 담는다. */
// void store_to_writer_article_struct(char *user_id,  article* user_articles)
// {
//     char user_id_[30];  

//     strcpy(user_id_, user_id);
//     // printf("%s , 총 글의 갯수 %d", user_id_,articles_cnt);
//     int cnt=0;
//     for(int i=0; i<articles_cnt; i++)
//     {
//         if(strcmp(articles[i].writer_id, user_id)==0)
//         {
//             char temp[30]="";
//             // printf("작성자함수 %d번 글이 해당\n", articles[i].article_id);
//             // 구조체에 담아서 리턴
//             user_articles[cnt].article_id = articles[i].article_id;
//             strcpy(user_articles[cnt].article_title, articles[i].article_title);
//             strcpy(temp,articles[i].writer_id);
//             strcat(temp, " : ");
//             strcat(temp,  articles[i].article_content);            
//             strcpy(user_articles[cnt].article_content, temp);  
//             // strcpy(user_articles[cnt].article_content, articles[i].article_content);
//             strcpy(temp,articles[i].writer_id);
//             strcpy(temp,articles[i].article_content);                  
//             strcpy(user_articles[cnt].writer_id, articles[i].writer_id);
//             strcpy(user_articles[cnt].reciever_id, articles[i].reciever_id);            
//             user_articles[cnt].write_time_1= articles[i].write_time_1;
//             strcpy(user_articles[cnt].write_time_2, articles[i].write_time_2);
//             user_articles[cnt].read_count = articles[i].read_count;
//             cnt++;
            
//         }
//         // printf("%s\n",articles[i].writer_id);
//     }    
// }

int * store_to_receiver_article_struct(char *user_id,  int* rv, int* wr)
{

    
    char user_id_[30];  
    int article_index[100];

    strcpy(user_id_, user_id);
    // printf("%s , 총 글의 갯수 %d\n", user_id_,articles_cnt); 400
    int cnt=0;
    // printf("1025라인 %s",user_id);
    for(int i=0; i<articles_cnt; i++)
    {
        
        if(strcmp(articles[i].reciever_id, user_id)==0)
        {
            rv[cnt] = articles[i].article_id;
            cnt++;
        }        
    }  

    for(int i=0; i<articles_cnt; i++)
    {
        if(strcmp(articles[i].writer_id, user_id)==0)
        {
            wr[cnt] = articles[i].article_id;
            cnt++;   
        }
        // printf("%s\n",articles[i].writer_id);
    } 

    

}

