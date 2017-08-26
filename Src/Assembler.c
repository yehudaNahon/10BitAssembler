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
    Assembly* assembly = context;
    char line[MAX_LINE_LEN];
    char* commandLine = line;
    char* label = NULL;
    Symbol symbol;
    
    if(!assembly || !data)
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
        commandLine = String_SplitToTwo(line, LABEL_INDICATOR);
        label = line;
        String_SimplfyLine(commandLine);
        String_SimplfyLine(label);
    }
    
    /*printf("%s : %s - %s\n",label,commandLine,params);*/
    
    if(DataHandler.IsHandler(commandLine))
    {
        if(label)
        {
            symbol = Symbol_Init(label,assembly->prog.data.counter + 1);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));
        }
        
        assembly->prog.data.counter += DataHandler.GetSize(commandLine);
        DataHandler.Add(commandLine,&assembly->prog.data.bytes,assembly->prog.symbols);
    }
    else if(CommandHandler.IsHandler(commandLine))
    {
        if(label)
        {
            symbol = Symbol_Init(label,assembly->prog.code.counter + 1);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));    
        }
        assembly->prog.code.counter += CommandHandler.GetSize(commandLine);
        
        /* add the pennding queue*/
        Queue_enqueue(&assembly->penndingCommands, commandLine, String_Len(commandLine) + 1);
    }
}

void Assembler_ParseCommands(const void* data, size_t len, void* context)
{
    Programme* prog = context;
    char line[MAX_LINE_LEN];
    char* commandLine = line;
    char* params = NULL;
    
    if(!prog || !data || len == 0)
    {
        return;
    }
    /* copy the line to a buffer to mess oround with*/
    Memory_Copy(line, data, len);
    
    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    /*should always be true*/
    if(CommandHandler.IsHandler(commandLine))
    {
        CommandHandler.Add(commandLine,&prog->code.bytes,prog->symbols);
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
    Programme* prog = &assembly.prog;
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
    List_ForEach(assembly.prog.data.bytes, &PrintByte, NULL);

    printf("*********** SYMBOLS************\n");
    List_ForEach(assembly.prog.symbols, &PrintSymbol, NULL);
    
    Queue_ForEach(assembly.penndingCommands, &Assembler_ParseCommands, &assembly.prog);
    
    printf("********** CODE **************\n");
    /*printf("%lu %p\n",List_Len(assembly.prog.code.bytes),&prog->code.bytes);*/
    List_ForEach(assembly.prog.code.bytes,&PrintByte,NULL);
    
    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    Assembly_Delete(&assembly);

    return true;
}







