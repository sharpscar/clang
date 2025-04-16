#include <stdio.h>
#include <time.h>


typedef struct {

    char date[100];
    char day_[10];
    int is_open;  // 1이면 영업 0이면 휴일
}bussiness_month_4



int main()
{
   
   time_t t= time(NULL);
   struct tm tm_ = *localtime(&t);
   char *DayOfTheWeek[] = {"일","월","화","수","목", "금","토"};
   int DayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
   
   char str_t[100];
   sprintf(str_t,"%d-%d-%d %d:%02d:%02d", 
            tm_.tm_year+1900,
            tm_.tm_mon+1,
            tm_.tm_mday,
            tm_.tm_hour,
            tm_.tm_min,
            tm_.tm_sec);

    /** 날짜정보 */
    printf("%s\n", str_t);

   int total;
   /**a는 월 b는 일 요일은 total%7에서 위 배열에서 가져온다. */
   int a=tm_.tm_mon+1;
   int b=tm_.tm_mday;
    char the_day[10];
   while(a>0){
    total +=DayOfMonth[--a];
   }   
   total += b;
   strcpy(the_day,DayOfTheWeek[total%7] );
   
   //요일
   printf("%s요일 입니다.",the_day);
   
//    sprintf(str_t, )




    return 0;
}


