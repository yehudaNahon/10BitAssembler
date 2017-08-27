#include "Memory.h"
#include "Convert.h"
#include "Assembly.h"
#include "EntryHandler.h"
#include "String.h"
#include "Log.h"
#include "File.h"
#include "Symbol.h"

/*
    check if the line is a entry command
*/
#define ENTRY_COMMAND_STR (".entry")
bool EntryHandler_ISHandler(const char* line)
{
    return String_Compare(line,ENTRY_COMMAND_STR,String_Len(ENTRY_COMMAND_STR)) == 0;
}

/*
    update symbol list to entry command
*/
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

    /*copy the line to a buffer for manipulation*/
    String_Copy(buffer,line,sizeof(buffer));

    /*find parameter in line*/
    symbolsPtr = String_FindChar(buffer,SPACE_CH);
    if(!symbolsPtr)
    {
        return false;
    }
    symbolsPtr++;

    /*splite the parameters to single symbols*/
    symbolStr = String_Split(symbolsPtr,COMMA_STR);
    if(!symbolStr)
    {
        return false;
    }
    
    do
    {
        /* find the symbol corresponding to the label*/
        List_FindData(*symbols,(void**)&symbol,&Symbol_Finder,symbolStr);
        if(symbol)
        {   
            Symbol_ChangeType(symbol,ePublic);
        }
        else
        {
            Log(eWarning,"could not find symbol :: %s",symbol);
            return false;
        }
    }while(!(symbolStr = String_Split(buffer,COMMA_STR)));

    return true;
}

/* return th size of the cpmmand*/
size_t EntryHandler_GetSize(const char* line)
{
    return 0;
}

/* a global struct of function pointer to the handler*/
Handler EntryHandler = {
    &EntryHandler_ISHandler,
    &EntryHandler_GetSize,
    &EntryHandler_Add
};

/*
    if the symbol provided is a entry symbol write it to file
*/
void EntryHandler_WriteEnteriesToFile(void* data,size_t len,void* context)
{
    char buffer[MAX_LINE_LEN];
    const Symbol* symbol = (Symbol*)data;
    FILE* file = context;

    if(!symbol || !file || symbol->type != ePublic)
    {
        return;
    }
    
    /*clean buffer*/
    Memory_Set(buffer,0,sizeof(buffer));
    
    /*append info to buffer*/
    String_Append(buffer,symbol->name,MAX_SYMBOL_NAME_LEN);
    String_Append(buffer,SPACE_STR,sizeof(SPACE_STR));
    Convert_DecimalToBase4Str(symbol->address,&buffer[String_Len(buffer)],sizeof(buffer) - String_Len(buffer),4);
    
    /*write the buffer to the file*/
    if(!File_WriteLine(file,buffer))
    {
        Log(eError,"Failed Writing to file :: %s",buffer);
    }
}

/*
    write all entry symbols in list to entry file
*/
bool WriteEntryFile(char fileName[],List* symbols)
{
    return File_WriteToFile(fileName,*symbols,&EntryHandler_WriteEnteriesToFile);
}
