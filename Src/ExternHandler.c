#include "ExternHandler.h"
#include "Assembly.h"
#include "String.h"
#include "Log.h"
#include "Operand.h"
#include "File.h"
#include "Memory.h"
#include "Convert.h"
#include "Symbol.h"

int counter = 0;

/*return if the command is a extern command*/
#define EXTERN_COMMAND_STR (".extern")
bool ExternHandler_ISHandler(const char* line)
{
    return String_Compare(line,EXTERN_COMMAND_STR,String_Len(EXTERN_COMMAND_STR)) == 0;
}

/*updates the symbol list with the extern commands*/
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

    /*copy line to buffer*/
    String_Copy(buffer,line,sizeof(buffer));

    /*find params*/
    symbolsPtr = String_FindChar(buffer,SPACE_CH);
    if(!symbolsPtr)
    {
        return false;
    }
    symbolsPtr++;
    
    /*split to params*/
    symbolStr = String_Split(symbolsPtr,COMMA_STR);
    if(!symbolStr)
    {
        return false;
    }
    
    do
    {
        /* for each param add to symbol list*/
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

/*writes extern symbol to file*/
int CommandCounter = 0;
List* pubSymbols = NULL;
void ExternHandler_WriteExternsToFile(void* data,size_t len,void* context)
{
    char buffer[MAX_LINE_LEN];
    Symbol* symbol = NULL;
    int address = 0;
    OperandByte* byte = (OperandByte*)data;
    FILE* file = context;
    
    CommandCounter++;
    
    /*check that its a valid byte*/
    if(!pubSymbols || !byte || !file || byte->type != eExternal)
    {
        return;
    }

    /*find the symbol that matches the byte*/
    address = byte->value;
    List_FindData(*pubSymbols,(void**)&symbol,&Symbol_ExternFinder,(void*)&address);
    if(!symbol)
    {
        Log(eError,"did not find extern symbol from commands");
        return;
    }
    
    /*clean the buffer*/
    Memory_Set(buffer,0,sizeof(buffer));

    /*append info to buffer*/
    String_Append(buffer,symbol->name,MAX_SYMBOL_NAME_LEN);
    String_Append(buffer,SPACE_STR,sizeof(SPACE_STR));
    Convert_DecimalToBase4Str(CommandCounter,&buffer[String_Len(buffer)],sizeof(buffer) - String_Len(buffer),4);

    /*set the bytes address to 0*/
    byte->value = 0;

    /*write the buffer to the file*/
    if(!File_WriteLine(file,buffer))
    {
        Log(eError,"Failed Writing to file :: %s",buffer);
    }
}


bool WriteExternFile(char* fileName,List* bytes,List* symbols,int baseAddress)
{
    CommandCounter = baseAddress - 1;
    pubSymbols = symbols;

    return File_WriteToFile(fileName,*bytes,&ExternHandler_WriteExternsToFile); 
}

