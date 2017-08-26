#include "Assembly.h"
#include "EntryHandler.h"
#include "String.h"
#include "Log.h"

#define ENTRY_COMMAND_STR (".entry")
bool EntryHandler_ISHandler(const char* line)
{
    return String_Compare(line,ENTRY_COMMAND_STR,String_Len(ENTRY_COMMAND_STR)) == 0;
}

bool EntryHandler_Add(const char* line,List* bytes,List* symbols)
{
    char buffer[MAX_LINE_LEN];
    char* symbolStr = NULL;
    char* symbolsPtr = NULL;
    Symbol* symbol = NULL;
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
        List_FindData(*symbols,(void**)&symbol,&Symbol_Finder,symbolStr);
        if(!symbol)
        {   
            Log(eWarning,"could not find symbol :: %s",symbol);
        }
        else
        {
            Symbol_ChangeType(symbol,ePublic);
        }
    }while(!(symbolStr = String_Split(buffer,COMMA_STR)));

    return true;
}

size_t EntryHandler_GetSize(const char* line)
{
    return 0;
}


Handler EntryHandler = {
    &EntryHandler_ISHandler,
    &EntryHandler_GetSize,
    &EntryHandler_Add
};



