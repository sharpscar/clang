#include <stdio.h>

#include <time.h>

typedef struct {

    char date[100];
    char day_[50];
    int is_open;  // 1이면 영업 0이면 휴일
}bussiness_month_4;
void solution(int a, int b, char *c);
void  get_current_time(char *current);
int main()
{
    /*
    get_current_time() 함수로 현재시간을 가져온다.     
    set_calendar () // 달력 [30] 객체를 리턴 <-- 이걸 이용해서 휴일을 지정할수 있습니다.  
    set_holiday()  <-- 만든 달력 객체에 휴일을 설정할수 있습니다. 

    is_open_for_business() <-- 만든 달력 객체를 활용해서 영업일인지 휴일인지 판별하는 함수입니다.    

    */

    bussiness_month_4 m4[32];

    set_calendar(m4); // m4를 달력 객체로 만들고  
    char current[30];
    get_current_time(current);
    printf("현재 날짜 %s", current);
    // free(current);

    return 0;
}

void  get_current_time(char *current)
{

    time_t t= time(NULL);
    struct tm tm_ = *localtime(&t);
    current = (char*)malloc(sizeof(char)*10);
    // memset(current, 0, sizeof(current));
    char str_t[100];
    sprintf(current,"%d-%d-%d %d:%02d:%02d", 
                tm_.tm_year+1900,
                tm_.tm_mon+1,
                tm_.tm_mday,
                tm_.tm_hour,
                tm_.tm_min,
                tm_.tm_sec);
    printf("%s", current);

    

}

void set_calendar(bussiness_month_4 *m4)
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




