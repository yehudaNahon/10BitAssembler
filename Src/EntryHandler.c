#include "Memory.h"
#include "Convert.h"
#include "Assembly.h"
#include "EntryHandler.h"
#include "String.h"
#include "Log.h"
#include "File.h"

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

void EntryHandler_WriteEnteriesToFile(const void* data,size_t len,void* context)
{
    char buffer[MAX_LINE_LEN];
    const Symbol* symbol = (Symbol*)data;
    FILE* file = context;
    if(!symbol || !file || symbol->type != ePublic)
    {
        return;
    }

    Memory_Set(buffer,0,sizeof(buffer));

    String_Append(buffer,symbol->name,MAX_SYMBOL_NAME_LEN);
    String_Append(buffer,SPACE_STR,sizeof(SPACE_STR));
    Convert_DecimalToBase4Str(symbol->address,&buffer[String_Len(buffer)],sizeof(buffer) - String_Len(buffer),4);

    if(!File_WriteLine(file,buffer))
    {
        Log(eError,"Failed Writing to file :: %s",buffer);
    }
}



bool WriteEntryFile(char fileName[],List* symbols)
{
    return File_WriteToFile(fileName,*symbols,&EntryHandler_WriteEnteriesToFile);
}
