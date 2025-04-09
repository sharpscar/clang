#include <stdio.h>
#include <string.h>
#include <stdlib.h> // to use qsort
#include <time.h>
#include "struct_member.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>


#define MAX_MEMBERS 100



// 글번호 / 글제목/ 컨텐츠/ 글작성자/ 받는분/ 작성시간 글
struct article {
    int article_id;
    char article_title[50];
    char article_content[500];
    char writer_id[50];
    char reciever_id[50];
    int write_time_1;
    char write_time_2[100];
    int read_count;
};
typedef enum
{
    OK,
    NO_MEMBER
}AccountError;

// 회원Txt 파일 -> 구조체 new_mem 파일에 담는 함수
void csv_to_struct_mem();

//글작성을 위해 글제목, 글내용 입력 받는 함수
struct article get_input_for_write_article();

// 글목록을 출력하는 함수
void show_article_list();

//글 작성 (유저)
void write_a_article();

/*삭제를 하기위해 구조체 배열 변수에 파일의 내용들을 담는 함수*/
void store_to_article_struct(); 
/**관리자 글을 구조체로 실행하고 나면 admin_articles 변수와 admin_articls_cnt변수를 참조할수 있다. */
void store_to_admin_article_struct(); 

void delete_a_article_from_articles();
void delete_a_article_from_admin_articles(int del_index);
struct article articles[300]; 
struct article admin_articles[300]; 

member new_mem[100];
int articles_cnt;
int admin_articles_cnt;
int account_cnt;

/* 회원 아이디로 검색
found_account : 검색된 회원의 구조체의 인덱스
id_account    : 찾고자 하는 회원의 id (문자열)
*/
void  retrieve_id_from_member(int* found_account, char id_account[]);
/*admin이 공지사항처럼 모두에게 메시지를 남기는 함수*/
void write_a_admin_article();

//정렬을 위한 함수
int comfunc_by_member_name(const void *a, const void *b);
/* 회원 이름순으로 정렬*/
void order_by_account_name();
/* 관리자는 회원의 비밀번호를 제외한 모든 정보를 볼수 있다.*/
void admin_can_check_account_info();

int main()
{  
    sync_for_admin();
    return 0;
}

/*운영자가 article.txt파일을 토대로 파일을 생성하는 함수 */
void sync_for_admin()
{
    store_to_article_struct();
    // struct article articles[300]; 
    //articles 라는 변수가 생김 아마 15개?
    // printf("글의 갯수 아마 15개 %d\n", articles_cnt);
    for(int i=0; i<articles_cnt; i++)
    {
        char s1[10];
        char dir_name[50];
        char file_name[50];
        // 뭟하려하는가? 일단 작성자와 받는이가 각각 존재하는지 확인
        // 둘다 존재하면 받는이의 디렉토리를 생성하고 파일을 생성
        if(strcmp(articles[i].reciever_id, " ")==0)
        {               
         //이부분에서 디렉토리 변수/파일.txt를 문자열로 생성하고 (if문 바깥, for문 안)에서 파일을 그 문자열로 파일을 생성
            // int result;
            // result = do_mkdir(articles[i].writer_id, 0755);
            strcpy(dir_name,"server/");
            strcpy(dir_name,articles[i].writer_id );//작성자id_ 
            strcpy(file_name,articles[i].writer_id ); //글id
            strcat(file_name,"_");
            sprintf(s1,"%d",articles[i].article_id);
            strcat(file_name,s1);
            strcat(file_name,".txt");
            // printf("test %s/ %s\n", dir_name, file_name );

        }else if(strcmp(articles[i].reciever_id," ") !=0)
        {            
        //    보내기의 경우 writer_id로 디렉터리 만드는게 아니라 받는이로 디렉터리를 만들어야함
            // int result;
            // result = do_mkdir(articles[i].writer_id, 0755);
            strcpy(dir_name,"server/");
            strcat(dir_name,articles[i].reciever_id );//작성자id_ 
            strcpy(file_name,articles[i].writer_id ); //글id
            strcat(file_name,"_");
            sprintf(s1,"%d",articles[i].article_id);
            strcat(file_name,s1); 
            strcat(file_name,".txt");
            // printf("test %s/ %s\n", dir_name, file_name );
        }

        do_mkdir(dir_name,0755);

        strcat(dir_name,"/");
        strcat(dir_name, file_name);
        // printf("test %s\n", dir_name );
        // strcpy(articles[i].file_address , dir_name);

        FILE *file = fopen(dir_name, "w");

        if(file== NULL)
        {
            printf("파일을 열수 없습니다.");
            exit(1);
        }
        fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d\n",
            articles[i].article_id,
            articles[i].article_title,
            articles[i].article_content,
            articles[i].writer_id,
            articles[i].reciever_id,
            articles[i].write_time_1,
            articles[i].write_time_2 ,
            articles[i].read_count
            // articles[i].file_address
           );               
           fclose(file);    
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
        // for(int i=0; i<cnt;i++)
        // {   
        //     int index_ =found_account[i];
        //     printf("%d\n",index_);
        //     printf(" 찾은놈 아이디 : %s\n",  new_mem[index_].id);
        // }
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

void write_a_article()
{
    FILE *file = fopen("./article.txt","a");

    if(file ==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        exit (1);
    }
    // 입력을 받는 함수/  사용자로부터 입력받는 필드 글제목, 컨텐츠
    

    // 받은 입력을 구조체에 넣는 함수/ 입력외에 들어가는 정보들 article 마지막id, user_id, time_t

    char user_id[50] = "박경태01";
    // char sender_id[3]= " ";  //없으면 공백으로 쓰자
    char receiver_id[50] =" ";
    time_t seconds;
    time(&seconds);

    struct article a;
    a = get_input_for_write_article();
    a.article_id = 17;   
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
    fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d\n",
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
}
void write_a_admin_article()
{
    FILE *file = fopen("./admin_article.txt","a");

    if(file ==NULL)
    {
        printf("파일을 열수 없습니다.\n");
        exit 1;
    }
    // 입력을 받는 함수/  사용자로부터 입력받는 필드 글제목, 컨텐츠
    

    // 받은 입력을 구조체에 넣는 함수/ 입력외에 들어가는 정보들 article 마지막id, user_id, time_t

    char user_id[50] = "0";
    // char sender_id[3]= " ";  //없으면 공백으로 쓰자
    char receiver_id[50] =" ";
    time_t seconds;
    time(&seconds);

    struct article a;
    a = get_input_for_write_article();
    a.article_id = 17;   
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
    fprintf(file ,"%d|%s|%s|%s|%s|%d|%s|%d\n\n",
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
}


struct article get_input_for_write_article()
{
    struct article a;
    char title[50];
    char content[500];

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


void csv_to_struct_mem() {  // 멤버 csv 내부 텍스트 메인함수 구조체로 가져오는 함수
    FILE *file = fopen("account.txt","r");
    char line[255];
    account_cnt = 0;

    while(fgets(line, sizeof(line),file) != NULL && account_cnt < MAX_MEMBERS){
        // line[strcpn(line,"\n")] = 0;  //줄바꿈 문자 0으로 바꿔줌
        char *token = strtok(line,"|");  //,기준으로 나누어 가져오겟다

        if(token == NULL) continue;
            strcpy(new_mem[account_cnt].id, token);
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[account_cnt].password, token);
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[account_cnt].name, token);            
            token = strtok(NULL, "|");

        if (token == NULL) continue;
            strcpy(new_mem[account_cnt].phone_num, token);
            token = strtok(NULL, "|");
           

        if (token == NULL) continue;
            new_mem[account_cnt].age = atoi(token);           
        
        account_cnt++;

    }
    fclose(file);


}
