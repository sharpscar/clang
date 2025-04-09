typedef struct 
{
    char id [40];
    char password[40];
    char name[20];
    int age;
    char phone_num[20];

}member;



typedef struct{
    int article_id;
    char article_title[50];
    char article_content[500];
    char writer_id[50];
    char reciever_id[50];
    int write_time_1;
    char write_time_2[100];
    int read_count;
    char file_address[100];
}article;
