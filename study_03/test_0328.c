#include <stdio.h>
#include <stdlib.h>

int main() 
{
    // printf("/home/scar/c_workspace/miniproject/study");

    FILE *fp = NULL;
    // fp = fopen("/home/scar/c_workspace/miniproject/study/test.txt","r");  // "./test.txt"
    fp = fopen("/home/scar/c_workspace/miniproject/study/friend.c","r");  // "./test.txt"

    // if(fp == NULL)
    // {
    //     perror("파일을 열수 없습니다.");
    //     return EXIT_FAILURE;
    // }

    // char ch;
    // // 이 파일이 끝날때까지  한글자씩 읽어서 터미널에 뿌린다?
    // while((ch=getc(fp))!=EOF)
    // {
    //     putc(ch, stdout);
    // }

    // char ch[10];
    // while(fscanf(fp, "%s", ch)==1){
    //     printf("%s\n",ch);
    // }
    
    // 파일리딩
    char* ch;
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    ch = malloc(file_size * sizeof(char) +1);
    fread(ch, sizeof(char), file_size, fp);
    ch[file_size] = '\0';
    fclose(fp);
    printf("%s", ch);


    //정적인 크기로 새로쓰자
    // FILE* fp = NULL;  

    // fp = fopen("./write.txt", "a");

    // char ch[255];
    // scanf("%[^\n]s", ch);

    // fprintf(fp, "%s\n", ch);

    // char* ch;
    // ch = malloc(10* sizeof(char));
    // char c;
    // int size = 0;
    // while((c=getchar())!= '\n')
    // {
    //     if(size >= sizeof(ch))        
    //     {
    //      ch = realloc(ch(size+10) * sizeof(char))   ;
    //     }
    //     ch[size++] = c;

    // }

    // ch[size] = '\0';


    free(ch);
    printf("%s", ch);





    fclose(fp);  // 파일을 닫음 
    return 0;
}