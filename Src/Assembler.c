#include <stdint.h>
#include <stdio.h>
#include "BitArray.h"
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
#include "CommandByte.h"

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
    size_t size = 0;
    
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
        /* need to find a better solution*/
        while(!String_IsLetter(*commandLine) && *commandLine != '.') commandLine++;
    }
    
    
    /*printf("%s : %s - %s\n",label,commandLine,params);*/
    
    if(DataHandler.IsHandler(commandLine))
    {
        if(label)
        {
            symbol = Symbol_Init(label,assembly->prog.data.counter);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));
        }
        size = DataHandler.GetSize(commandLine);
        if(size == 0)
        {
            Log(eError,"un supported data command operand: %s",commandLine);
            /*print a warning of a wrong command*/
        }
        else
        {
            assembly->prog.data.counter += size;
            DataHandler.Add(commandLine,&assembly->prog.data.bytes,assembly->prog.symbols);
        }

    }
    else if(CommandHandler.IsHandler(commandLine))
    {
        if(label)
        {
            symbol = Symbol_Init(label,assembly->prog.code.counter);
            List_Add(&assembly->prog.symbols, &symbol, sizeof(Symbol));    
        }
        size = CommandHandler.GetSize(commandLine);
        if(size == 0)
        {
            Log(eError,"un supported command operands: %s",commandLine);
        }
        else
        {
            assembly->prog.code.counter += size;
            Queue_enqueue(&assembly->penndingCommands, commandLine, String_Len(commandLine) + 1);
        }
        
        /* add the pennding queue*/
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
    printf("%s\n",(char*) data);
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

    /* for code testing need to remove*/
    assembly.prog.code.counter = 100;
    assembly.prog.data.counter = 122;

    /* create symbol table*/
    File_ForEach(file, &Assembler_CreateSymbols,&assembly);

    printf("******** DATA MEMORY **************\n");
    List_ForEach(assembly.prog.data.bytes, &PrintBitsIter, NULL);

    printf("*********** SYMBOLS************\n");
    List_ForEach(assembly.prog.symbols, &PrintSymbol, NULL);
    printf("\n\n");    
    Queue_ForEach(assembly.penndingCommands, &Assembler_ParseCommands, &assembly.prog);
    printf("\n\n");
    printf("********** CODE **************\n");
    /*printf("%lu %p\n",List_Len(assembly.prog.code.bytes),&prog->code.bytes);*/
    List_ForEach(assembly.prog.code.bytes,&PrintBitsIter,NULL);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    Assembly_Delete(&assembly);

    return true;
}







