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

#define LABEL_INDICATOR (':')
#define LABEL_SPLITER (" :")
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH
#define WASTE_STR ("    \n\t")
#define SPACE_STR (" ")

bool Assembler_IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = File_FindDot(fileName);
	
	return ptr == NULL || String_Compare(ptr,ASSEMBLY_END) == 0;
}

/*
    print the line given to stdout
*/
void Assembler_PrintLine(char* line, size_t index, void* context)
{
    Assembler_CleanLine(line);
    printf("%s\n", line);
}


bool Assembler_IsCodeLine(char* line)
{
    /* for now will only check that its not a comment*/
    if(String_FindChar(line,';') || String_FindChar(line, '.'))
    {
        return false;
    }

    return true;
}

bool Assembler_IsActionLine(char* line)
{
    return true;
}

/* cleans the line from un needed spaces and tabs*/
void Assembler_CleanLine(char* line)
{
    char* word = NULL;
    /*create buffer in the line size*/
    size_t length = String_Len(line);
    char* buffer = (void*)Memory_Allocate(length);
    if(!buffer)
    {
        Log(eError,MEMORY_ERR);
    }
    /*clean buffer*/
    Memory_Set(buffer,0,length);

    /* spite to single words and create a new sentence only with the basic signs*/
    word = String_Split(line, WASTE_STR);
    do
    {
        String_Append(buffer,word,length);
        String_Append(buffer,SPACE_STR,length);
    }while((word = String_Split(NULL, WASTE_STR)));

 
    /* copy back the info to line*/
    String_Copy(line,buffer,length);
    /*release resources*/
    Memory_Delete(buffer);
}

/**
    Recieve a line from a file if the line has a label on it add it to the programme
*/
void Assembler_SearchLabel(char* line, size_t index,void* ptr)
{
    char* word = NULL;
    Assembly* assembly = (Assembly*) ptr;
    Symbol symbol;
    if(!line || !assembly)
    {
        return;
    }

    /*clean the line from extra info*/
    Assembler_CleanLine(line);

    
    if(Assembler_IsCodeLine(line))
    {
        assembly->lineCount++;

    }

    /* search for the label indicator in the file*/
    if(String_HasChar(line,LABEL_INDICATOR))
    {
        word = String_Split(line,LABEL_SPLITER);
        if(String_OnlyWithChars(word, LIGAL_LABEL_CH))
        {
            /* for now wont allow space between label and : wil correct in the future*/
            symbol = Symbol_Init(word, assembly->lineCount);
            SymbolTable_AddSymbol(&assembly->symbolTable, &symbol);
        }
    }
}

void Assembler_CreateCommand(char* line, size_t index,void* ptr)
{
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
    if(!File_ForEachLine(file, &Assembler_PrintLine, &assembly))
    {
        Log(eError,"Could not read data from file");
        return false;
    }


    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}







