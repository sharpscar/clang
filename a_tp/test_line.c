#include <stdio.h>

int main()
{

    int line;
    line = getTotalLine("admin_article.txt");
    printf("%d", line);
    return 0;
}

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