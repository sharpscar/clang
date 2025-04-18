#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>

/**
     * 대출을 발생시키기 위한 매개변수
     * 1. user_id <--대출신청한 사용자의 id 
     * 2. books_isbn[] 대출도서의 isbn들 (int형 배열)
     * 3. checkout_date 대여일
     * 4. return_date 반납일
     */
typedef struct {
    int checkout_id;
    char user_id[50];
    char books_isbn[10][20]; // 빌린도서의 isbn 문자열
    char checkout_date[50];
    
}checkout_books;

char *  get_current_time();
/*json 파일이 생성이 되긴 하는데 형식이 틀어진다. 98라인 , 쉼표가 마지막엔 
붙지 말아야한다.*/

int main()
{

    checkout_books cb[10];  //대여를 시험삼아 5개만 만들어보자 그리고 이걸 json으로 저장해보자 
    
    
    // char user_id[50];
    // long isbns[10]; 
    // char ch_date[50];
    memset(cb, 0, sizeof(cb));  
    /**test */
    cb[0].checkout_id = 1;
    strcpy(cb[0].user_id ,"my_id");
    strcpy(cb[0].books_isbn[0],"9788956604992");
    strcpy(cb[0].books_isbn[1],"9788954641630");
    strcpy(cb[0].books_isbn[2],"9788954650212");
    strcpy(cb[0].books_isbn[3],"9791190090261");
    strcpy(cb[0].checkout_date, get_current_time());     // current time가져오면됨 
    cb[1].checkout_id = 2;
    strcpy(cb[1].user_id ,"your_id");
    strcpy(cb[1].books_isbn[0], "9791191824001");
    strcpy(cb[1].books_isbn[1], "9788954654753");
    strcpy(cb[1].books_isbn[2], "9788997962129");
    strcpy(cb[1].books_isbn[3], "9791160406504");
    strcpy(cb[1].books_isbn[4], "9788934985051");     
    strcpy(cb[1].checkout_date, get_current_time());    

    cb[2].checkout_id = 3;
    strcpy(cb[2].user_id ,"our_id");
    strcpy(cb[2].books_isbn[0], "9788936456894");
    strcpy(cb[2].books_isbn[1], "9788936433598");
    strcpy(cb[2].books_isbn[2], "9791188862290");
    strcpy(cb[2].books_isbn[3], "9788936434496");
    strcpy(cb[2].books_isbn[4], "9788954655972");     
    strcpy(cb[2].checkout_date, get_current_time());
    

    cb[3].checkout_id = 4;
    strcpy(cb[3].user_id ,"new_id");
    strcpy(cb[3].books_isbn[0],"9788936456894");  
    strcpy(cb[3].books_isbn[3],"9788956609959");
    strcpy(cb[3].books_isbn[4],"9788954681155");     
    strcpy(cb[3].checkout_date, get_current_time());
    

    cb[4].checkout_id = 5;
    strcpy(cb[4].user_id ,"old_id");
    strcpy(cb[4].books_isbn[0], "9791191114225");
    strcpy(cb[4].books_isbn[1], "9791190090018");
    strcpy(cb[4].books_isbn[2], "9791197377143");    
    strcpy(cb[4].books_isbn[4], "9788954672214");    
    strcpy(cb[4].checkout_date, get_current_time());
    
    FILE *fp = fopen("checkout.json", "a");

    fprintf(fp, "[");


    // 임의로 5개의 정보를 넣었다. 
    for(int i=0; i<5; i++)
    {
        fprintf(fp, "{\n");

        fprintf(fp, "\"유저 아이디\" :\"%s\",\n",cb[i].user_id);
        // printf("도서isbn :%d\n",cb[i].books_isbn[1]);
        fprintf(fp, "\"대출일\" : \"%s\", \n",cb[i].checkout_date );
        fprintf(fp, "\"대여정보\" : \n");       
        fprintf(fp, "{\n"); 
        for(int j=0; j<10; j++)
        {
            // isbn은 13자리여야 하고 0보다 커야한다.
            if(strlen(cb[i].books_isbn[j]) >= 13)
            {                               
                fprintf(fp, "\"isbn\" :\"%s\",\n",cb[i].books_isbn[j]);               
                printf("\"도서isbn\" :\"%s\",\n",cb[i].books_isbn[j]);
            }
        }
        fprintf(fp, "},\n");
    }
    fprintf(fp, "]\n"); //전체닫기
    fclose(fp);
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
