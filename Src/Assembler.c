#include <stdint.h>
#include <stdio.h>

#include "Assembler.h"
#include "AssemblerInternals.h"
#include "Assembly.h"
#include "Log.h"
#include "File.h"
#include "String.h"
#include "SymbolTable.h"
#include "Queue.h"
#include "Memory.h"
#include "LinkedList.h"
#include "GeneralMacros.h"
#include "CommandHandler.h"
#include "DataHandler.h"

#define LABEL_INDICATOR (':')
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH

#define MAX_LINE_LEN (800)
#define COMMENT_CH (';')


bool Assembly_IsComment(const char* line)
{
    return line ? line[0] == COMMENT_CH : false;
}

bool Assembly_HasLabel(const char* line)
{
    /*TODO : add more tests*/
    if(String_FindChar(line,LABEL_INDICATOR))
    {
        return true;
    }

    return false;
}



bool Assembler_IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = File_FindDot(fileName);
	
	return ptr == NULL || String_Compare(ptr, ASSEMBLY_END, String_Len(ASSEMBLY_END)) == 0;
}


/*
    return whether or not the line
*/
bool Assembler_IsCodeLine(char* line)
{
    /* for now will only check that its not a comment*/
    if(String_FindChar(line,';'))
    {
        return false;
    }

    return true;
}

void Assembler_CreateSymbols(const void* data, size_t len, void* context)
{
    Assembly* prog = context;
    char line[MAX_LINE_LEN];
    char* command = line;
    char* params = NULL;
    char* label = NULL;
    Symbol symbol;
    
    if(!prog || !data)
    {
        return;
    }
    
    /* copy the line to a buffer to mess oround with*/
    Memory_Copy(line, data, len);

    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    /* if the line is not of a use to me ignore it*/
    if(String_Empty(line) || Assembly_IsComment(line))
    {
        return;
    }
    
    if(Assembly_HasLabel(line))
    {
        command = String_SplitToTwo(line, LABEL_INDICATOR);
        label = line;
        String_SimplfyLine(command);
        String_SimplfyLine(label);
    }
    
    params = String_SplitToTwo(command, SPACE_CH);
    
    /*printf("%s : %s - %s\n",label,command,params);*/

    if(DataHandler_IsLine(command))
    {
        if(label)
        {
            symbol = Symbol_Init(label,prog->data.counter + 1);
            SymbolTable_Add(&prog->symbol, symbol);
        }
        prog->data.counter += DataHandler_Handle(command,params, &prog->data.memory);
    }
    else if(CommandHandler_IsLine(command))
    {
        if(label)
        {
            symbol = Symbol_Init(label,prog->command.counter + 1);
            SymbolTable_Add(&prog->symbol, symbol);    
        }
        prog->command.counter += CommandHandler_GetLineSize(command);
        
        if(params)
        {
            *(params - 1) = SPACE_CH;
        }
        /* add the pennding queue*/
        Queue_enqueue(&prog->penndingCommands, command, String_Len(command) + 1);
    }
}

void Assembler_ParseCommands(const void* data, size_t len, void* context)
{
    Assembly* prog = context;
    char line[MAX_LINE_LEN];
    char* command = line;
    char* params = NULL;
    
    if(!prog || !data)
    {
        return;
    }
    /* copy the line to a buffer to mess oround with*/
    Memory_Copy(line, data, len);
    
    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    params = String_SplitToTwo(command, SPACE_CH);
    
    /*should always be true*/
    if(CommandHandler_IsLine(command))
    {
        printf("%s %s\n",command,params);
        CommandHandler_Handle(command,params, &prog->command.memory);
    }
}

void PrintSymbol(const void* data,size_t len, void* context)
{
    const Symbol* symbol = data;
    printf("%s : %lu ---- %s\n",symbol->name, symbol->address, symbol->type?"Private":"Public");
}

void PrintByte(const void* data,size_t len, void* context)
{
    const Byte* byte = data;
    printf("%d\n",byte->value);
}

void PrintLine(const void* data, size_t len, void* context)
{
    printf("%s\n",data);
}

bool Assembler_AssembleFile(char* asmFile)
{
    Assembly assembly = Assembly_Init(asmFile);

    /*open the file*/
    FILE* file = File_Open(asmFile, "r");

    if(!file)
    {
        Log(eError,"Could not open file");
        return false;
    }

    /* create symbol table*/
    File_ForEach(file, &Assembler_CreateSymbols,&assembly);

    printf("******** PENNDING COMMANDS ********\n");
    Queue_ForEach(assembly.penndingCommands,&PrintLine,NULL);

    printf("******** DATA MEMORY **************\n");
    ByteTable_ForEach(assembly.data.memory, &PrintByte, NULL);

    printf("*********** SYMBOLS************\n");
    SymbolTable_ForEach(assembly.symbol, &PrintSymbol, NULL);
    
    printf("\n");
    Queue_ForEach(assembly.penndingCommands, &Assembler_ParseCommands, &assembly);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}







