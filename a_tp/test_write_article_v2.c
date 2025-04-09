#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/** 디렉터리를 생성하는 함수 pasPathName   */
int do_mkdir(const char *pasPathName, mode_t mode)
{
    int nStatus =0;
    struct stat st;

    if(stat(pasPathName, &st )!=0)
    {
        if(0!=mkdir(pasPathName, mode ) && EEXIST !=errno)
        {
            nStatus = -1;
        }
    }
    else if(!S_ISDIR(st.st_mode))
    {
        nStatus =-1;
    }
    return (nStatus);
}

int main()
{
    //디렉터리를 생성하는 부분
    int nResult =0;
    nResult = do_mkdir("./test", 0755);
    if(0>nResult)
    {
        printf("디렉토리 생성 실패\n");
    }else{
        printf("디렉토리 생성성공\n");
    }

    // 파일을 생성하는 부분은 write_a_article 함수를 참조하면됨
    // 파일을 생성해서  해당 파일이 도착하는지까지 확인해야함 

    // 글 보내기의 경우 디렉토리를 상대방 아이디로 생성해야함
    //

    return 0;
}

