
/* 올바른 방식
parserFile에서 함수 3개가 호출된다
해당 함수들에서는 중첩된 if 문이 없고 읽고 유지하기 쉽게 이루어져있다. 
*/
typedef struct 

{
    FILE* file_pointer;
    char* buffer;
}FileParser;

int parserFile(char* file_name)
{
    int return_value;
    FileParser* parser = createParser(file_name);
    return_value = searchFileForKeywords(parser);
    cleanParser(parser);
    return return_value;
}

int searchFileForKeywords(FileParser* parser)
{
    if(parser ==NULL)
    {
        return ERROR;
    }

    while(fgets(parser->buffer, BUFFER_SIZE, parser->file_pointer)!=NULL)
    {
        if(strcmp("KEYWORD_ONE\n", parser->buffer) ==0)
        {
            return KEYWORD_ONE_FOUND_FIRST;
        }
        if(strcmp("KEYWORD_TWO\n", parser->buffer)==0)
        {
            return KEYWORD_TWO_FOUND_FIRST;
        }
    }
    return NO_KEYWORD_FOUND;
}

//사전 조건들을 만족하는지 체크 A guard clause 
FileParser* createParser(char* file_name)
{
    assert(file_name!=NULL && "Invalid filename");
    FileParser* parser = malloc(sizeof(FileParser));
    if(parser)
    {
        parser->file_pointer = fopen(file_name, "r");
        parser->buffer = malloc(BUFFER_SIZE);
        if(!parser->file_pointer || !parser->buffer)
        {
            cleanupParser(parser);
            return NULL:
        }
    }
    return parser;
}

void cleanupParser(FileParser* parser)
{
    if(parser)
    {
        if(parser->buffer)
        {
            free(parser->buffer);
        }
        if(parser->file_pointer)
        {
            fclose(parser->file_pointer);
        }
        free(parser);
    }
}