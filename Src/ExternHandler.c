#include "ExternHandler.h"
#include "Assembly.h"
#include "String.h"
#include "Log.h"

int counter = 0;

#define EXTERN_COMMAND_STR (".extern")
bool ExternHandler_ISHandler(const char* line)
{
    return String_Compare(line,EXTERN_COMMAND_STR,String_Len(EXTERN_COMMAND_STR)) == 0;
}

bool ExternHandler_Add(const char* line,List* bytes,List* symbols)
{
    char buffer[MAX_LINE_LEN];
    char* symbolStr = NULL;
    char* symbolsPtr = NULL;
    Symbol symbol;
    if(!line)
    {
        return false;
    }

    
    String_Copy(buffer,line,sizeof(buffer));

    symbolsPtr = String_FindChar(buffer,SPACE_CH);
    if(!symbolsPtr)
    {
        return false;
    }
    symbolsPtr++;
    
    symbolStr = String_Split(symbolsPtr,COMMA_STR);
    if(!symbolStr)
    {
        return false;
    }
    
    do
    {
        symbol = Symbol_Init(symbolStr,counter,eExternalSymbol); 
        counter++;
        List_Add(symbols,&symbol,sizeof(symbol));
    }while(!(symbolStr = String_Split(buffer,COMMA_STR)));

    return true;
}

size_t ExternHandler_GetSize(const char* line)
{
    return 0;
}


Handler ExternHandler = {
    &ExternHandler_ISHandler,
    &ExternHandler_GetSize,
    &ExternHandler_Add
};



