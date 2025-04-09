#include <stdio.h>
#define ERROR 404
int main()
{


    return 0;
}

//아마도 파일을 다루는 함수같앙~
int parseFile(char* file_name)
{
    int return_value = ERROR;  //흐응 몰라서 걍 404 세팅! 
    FILE* file_pointer = 0; // 파일포인터 초기화
    char* buffer =0;       //?

    assert(file_name!=NULL && "Invalid filename");
    
    if(!(file_pointer=fopen(file_name, "r")))
    {
        goto error_fileopen;
    }
    if(!(buffer=malloc(BUFFER_SIZE)))
    {
        goto error_malloc;
    }
    return_value = searchFileForKeywords(buffer, file_pointer);
    free(buffer);

    error_malloc:
        fclose(file_pointer);
    error_fileopen:
        return return_value;

}
int parseFile_1(char* file_name)
{
    int return_value = ERROR;
    FILE* file_pointer = 0;
    char* buffer =0 ;
    assert(file_name!=NULL && "Invalid filename");
    if((file_pointer=fopen(file_name, "r")) && (buffer=malloc(BUFFER_SIZE)))
    {
        return_value = searchFileForKeywords(buffer, file_pointer);
    }
    if(file_pointer)
    {
        fclose(file_pointer);
    }
    if(buffer)
    {
        free(buffer);
    }
    return return_value;
}


//좋은 사례

void someFunction()
{
    int r1,r2;
    if((r1=allocateResource1()) && (r2=__allocateResource2()))
    {
        mainFunctionality();
    }
    if(r1)
    {
        cleanupResource1();
    }
    if(r2)
    {
        cleanupResource2();
    }
}

