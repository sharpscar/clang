#include <stdio.h>

typedef enum
{
    MINOR_ERROR,
    MAJOR_ERROR,
    UNKNOWN_ERROR,
    OK
}ErrorCode;

int main()
{
    ErrorCode status = func(); //함수를 호출하고 호출결과를(에러코드)를 status에 담는다.

    if(status==MAJOR_ERROR|| status ==UNKNOWN_ERROR)
    {
        // 메이저한 오류(일상다반사) 거나 알수 없는 오류일땐?
        /* abort program*/
    }
    else if(status == MINOR_ERROR)
    {
        /*handle 미니어한 에러 error */
    }
    else if(status ==OK)
    {
        /* continue normal execution 모든 상태가 오케이 */
    }

    return 0;
}

ErrorCode func()
{
    if(minorErrorOccurs())
    {
        return MINOR_ERROR;
    }
    else if(majorErrorOccurs())
    {
        return MAJOR_ERROR;
    }else if(internalError1Occurs()||internalError2Occurs())
    {
        return UNKNOWN_ERROR;
    }
    else{
        return OK;
    }
}