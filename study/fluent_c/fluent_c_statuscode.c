#include <stdio.h>

typedef enum
{
    MINOR_ERROR,
    MAJOR_ERROR,
    OK
}ErrorCode;

int main()
{

    ErrorCode status = func();
    if(status == MAJOR_ERROR)
    {
        //abort program
    }
    else if(status == MINOR_ERROR)
    {
        // handle error

    }
    else if(status ==OK)
    {
        // continue normal execution
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
    }else{
        return OK;
    }
}

/*Regeistry Api

*/

typedef enum
{
    OK,
    OUT_OF_MEMORY,
    INVALID_KEY,
    INVALID_STRING,
    STRING_TOO_LONG,
    CANNOT_ADD_KEY
}RegError;

/* Handle for registry keys */
typedef struct Key* RegKey;

/*
 Create a new registry key identified via the provided 'key_name' 
 Returns OK if no problem occurs, 
 INVALID_KEY if the 'key' parameter is NULL, 
 INVALID_STRING if 'key_name' is NULL, 
 STRING_TOO_LONG if 'key_name is too long, 
 OUT_OF_MEMORY if no memory resources are available.
*/
RegError createKey(char* key_name, RegKey* key);

/*
Store the provided 'value' to the provided 'key' 
Returns OK if no problem occurs, 
INVALID_KEY if the 'key' parameter is NULL,
INVALID_STRING if 'value' is NULL,
STRING_TOO_LONG if 'value' is too long. 
*/
RegError storeValue(RegKey key, char* value);

/*
Make the key available for being read. Returns OK nno problem occurs,
INVALID_KEY if 'key' is NULL, or 
CANNOT_ADD_KEY if the registry is full and no more keys can be published.
*/
RegError publishKey(RegKey key);
