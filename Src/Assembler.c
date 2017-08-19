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
#include "Handlers.h"

#define LABEL_INDICATOR (':')
#define LABEL_SPLITER (":")
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH

#define MAX_LINE_LEN (80)
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


void Assembler_AddToLinkedList(void* line, size_t* len, void* context)
{
    LinkedList* list = (LinkedList*)context;
    if(list)
    {
        LinkedList_Add(list, line, *len);
    }

}

void Assembler_CreateAssembly(void* data, size_t* len, void* context)
{
    Assembly* prog = context;
    char* line = data;
    char* label = NULL;
    Symbol symbol;

    if(!prog || !line)
    {
        return;
    }

    /* clean the line from tabs and stuff*/
    String_SimplfyLine(line);

    /* if the line is not of a use to me ignore it*/
    if(String_Empty(line) || Assembly_IsComment(line))
    {
        return;
    }
    
    if(Assembly_HasLabel(line))
    {
        label = String_Split(line, LABEL_SPLITER);
        line = String_Split(NULL, LABEL_SPLITER);
        String_SimplfyLine(line);
        String_SimplfyLine(label);
    }
    
    if(DataHandler_IsDataLine(line))
    {
        prog->dataCounter += DataHandler_AddDataLine(line, NULL);
        if(label)
        {
            symbol = Symbol_Init(label,prog->dataCounter);
            SymbolTable_AddSymbol(&prog->dataSymbols, &symbol);
        }
    }
    else if(CommandHandler_IsCommandLine(line))
    {
        prog->instructionCounter += CommandHandler_AddCommandLine(line, NULL);
        if(label)
        {
            symbol = Symbol_Init(label,prog->instructionCounter);
            SymbolTable_AddSymbol(&prog->codeSymbols, &symbol);    
        }
    }
}


bool Assembler_AssembleFile(char* asmFile)
{
    Assembly assembly = Assembly_Init(asmFile);

    /*open the file*/
    FILE* file = File_Open(asmFile, "r");

    if(!file)
    {
        Log(eError, "Could not open file");
        return false;
    }

    
    /* create symbol table*/
    File_ForEach(file, &Assembler_CreateAssembly,&assembly);

    printf("*********** DATA ************\n");
    SymbolTable_Print(&assembly.dataSymbols);

    printf("*********** CODE ************\n");
    SymbolTable_Print(&assembly.codeSymbols);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}







