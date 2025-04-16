#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {

    char date[100];
    char day_[50];
    int is_open;  // 1이면 영업 0이면 휴일
}bussiness_month;

void solution(int a, int b, char *c);
char *  get_current_time();
void is_open_now(bussiness_month *m4);
int main()
{
    /*
    get_current_time() 함수로 현재시간을 가져온다.   
    set_calendar () // 달력 [30] 객체를 리턴 <-- 이걸 이용해서 휴일을 지정할수 있습니다. 

    set_holiday(날짜정보)  <-- 만든 달력 객체에 휴일을 설정할수 있습니다. 
    set_workday(m4)
    
    is_open_for_business(날짜정보) <-- 만든 달력 객체를 활용해서 영업일인지 휴일인지 판별하는 함수입니다.    
    is_open_now()
    */

    bussiness_month m4[32];

    set_calendar(m4); // m4를 달력 객체로 만들고    
    
    char current[50];
    strcpy(current,  get_current_time());

    is_open_now(m4);
    // printf("%s", current);   
    
    // 1. 금일이 영업일이면 ok 영업일이 아니면 False
    // 2. 현재시간이 09~18시 이면 ok 
    // 1과 2가 통과되면 영업ok  is_open_now()?


    // printf("현재 날짜 시간은 : %s\n", current);

    // set_holyday(m4);
    // set_work_day(m4);
    // is_open_for_business(m4);  // 영업일인지 확인하는 함수


    return 0;
}

int is_open_now(bussiness_month *m4)
{
    int flag=0;

    time_t t= time(NULL);
    struct tm tm_ = *localtime(&t);
    char str_t[100];
    char *current;
    char yoil[10];

    solution(tm_.tm_mon+1, tm_.tm_mday, yoil);
    
    sprintf(str_t,"%d-%d-%d", 
                tm_.tm_year+1900,
                tm_.tm_mon+1,
                tm_.tm_mday                
            );
    

        
    //해당 날짜가 영업일인가? 맞으면 flag =1
    for(int i=0; i<31;i++)
    {
        
        if(strcmp(m4[i].date, str_t)==0)
        {
            if(m4[i].is_open ==1)
            {
                flag = 1;
        
            }else{
                flag = 0;
        
            }
        }
    }
    // 현재 시간이 8~18시 사이인가? 맞으면 1 틀리면 0
    if ( (tm_.tm_hour > 8) &&(tm_.tm_hour < 18))
    {
        flag = 1;
    }else{
        flag = 0;
    }   
    // printf("%d",flag);
    return flag;
   
}

void is_open_for_business(bussiness_month *m4)
{
    int a,b;
    printf("영업일인지 알아볼 날짜정보를 입력하세요 예 4월 24일: 4 24       \n");
    scanf("%d %d", &a, &b);

    char date_[50];
    sprintf(date_, "2025-%d-%d",a,b);

    if(a != 4)
    {
        printf("4월만 가능합니다 5월은 아직 기능이 완료되지 않았습니다.");
    }

    for(int i=0; i< 31; i++)
    {
        
        // printf("%s\n", m4[i].date);
        if(strcmp(m4[i].date, date_)==0)
        {
            
            if(m4[i].is_open ==1)
            {
                printf("%s 일은 영업일입니다.", m4[i].date);
            }
            else{
                printf("%s 일은 휴일입니다.", m4[i].date);

            }
            

        }
    }
}

void set_holyday(bussiness_month *m4)
{

    int a,b;
    int tmp=0;
    printf("휴일로 설정할 날짜정보를 입력하세요 예 4월 24일: 4 24       \n");
    scanf("%d %d", &a, &b);

    char date_[50];
    sprintf(date_, "2025-%d-%d",a,b);
    
    for(int i=0; i< 31; i++)
    {
        
        // printf("%s\n", m4[i].date);
        if(strcmp(m4[i].date, date_)==0)
        {
            // printf("%s %s\n",m4[i].date, date_);
            m4[i].is_open = 0;
            printf("%s를 휴일로 설정 완료!\n", m4[i].date);
            

        }
    }
    
}

void set_work_day(bussiness_month *m4)
{

    int a,b;
    printf("업무일로 설정할 날짜정보를 입력하세요 예 4월 24일: 4 24       \n");
    scanf("%d %d", &a, &b);

    char date_[50];
    sprintf(date_, "2025-%d-%d",a,b);
    
    for(int i=0; i< 31; i++)
    {
        // printf("%s\n", m4[i].date);
        if(strcmp(m4[i].date, date_)==0)
        {
            // printf("%s %s\n",m4[i].date, date_);
            m4[i].is_open = 1;
            printf("%s를 업무일로 설정 완료!\n", m4[i].date);
            

        }
    }
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

void set_calendar(bussiness_month *m4)
{

    // bussiness_month_4 m4[32];
    //달력 배열은 30개  날짜별로  날짜 , 요일, 영업유무를 담는다.

    //날짜와 요일을 만들고 영업유무에 값을 넣는 함수를 만든다. 
    char date_[50];
    char day_[10];
    for(int i=1; i<31; i++)
    {
        sprintf(date_ ,"2025-4-%d",i);
        // printf("%s  ",date_);
        strcpy(m4[i].date, date_);
        solution(4,i, day_);  //날짜를 넣어서 
        // printf("%s\n", day_);        
        strcpy(m4[i].day_,day_);        


        if((strcmp(m4[i].day_,"토")==0)||(strcmp(m4[i].day_,"일")==0))
        {
            m4[i].is_open = 0;
            // printf("휴일입니다.\n");
        }else{
            m4[i].is_open = 1;
            // printf("영업일입니다.\n");
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
  
   char the_day[10];
   while(a>0){
    Total +=DayOfMonth[--a];
   }   
   Total += b;
   
   strcpy(c,DayOfTheWeek[Total%7] );

}




