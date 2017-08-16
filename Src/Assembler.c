#include "Assembler.h"
#include "AssemblerInternals.h"
#include "Assembly.h"
#include "Log.h"
#include "File.h"
#include "String.h"
#include <stdint.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "Queue.h"
#include "Memory.h"
#include "LinkedList.h"
#include "GeneralMacros.h"

#define LABEL_INDICATOR (':')
#define LABEL_SPLITER (":")
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH

#define MAX_LINE_LEN (80)
#define COMMENT_CH (';')

#define DATA_NUM_OF_ELEM (3)
const char* dataInstructionsTable[MAX_LINE_LEN] = {
    ".data",
    ".mat",
    ".string"
};

#define COMMAND_NUM_OF_ELEM (16)
const char* commandInstructionsTable[MAX_LINE_LEN] = {
    "mov",
    "cmp",
    "add",
    "sub",
    "not",
    "clr",
    "lea",
    "inc",
    "dec",
    "jmp",
    "bne",
    "red",
    "prn",
    "jsr",
    "rts",
    "stop",
};


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

bool Assembly_IsData(const char* line)
{
    int i=0;
    for(i=0;i< DATA_NUM_OF_ELEM ; i++)
    {
        /*return true only if the strings are the same from the start*/
        if(!String_Compare(line, dataInstructionsTable[i], String_Len(dataInstructionsTable[i])))
        {
            return true;
        }
    } 

    return false;
}

bool Assembly_IsCommand(const char* line)
{
    int i=0;
    for(i=0;i< COMMAND_NUM_OF_ELEM ; i++)
    {
        /*return true only if the strings are the same from the start*/
        if(!String_Compare(line, commandInstructionsTable[i], String_Len(commandInstructionsTable[i])))
        {
            return true;
        }
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
    

    if(Assembly_IsData(line))
    {
        prog->dataCounter++;
        if(label)
        {
            symbol = Symbol_Init(label,prog->dataCounter);
            SymbolTable_AddSymbol(&prog->dataSymbols, &symbol);
        }
    }
    else if(Assembly_IsCommand(line))
    {
        prog->instructionCounter++;
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







