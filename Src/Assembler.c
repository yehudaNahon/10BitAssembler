#include "Assembler.h"
#include "AssemblerInternals.h"
#include "Assembly.h"
#include "Log.h"
#include "File.h"
#include "String.h"
#include <stdint.h>
#include <stdio.h>
#include "SymbolTable.h"

#define LABEL_INDICATOR (':')
#define LABEL_SPLITER (" :")
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH
#define SPACES_CH (" ")

bool Assembler_IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = File_FindDot(fileName);
	
	return ptr == NULL || String_Compare(ptr,ASSEMBLY_END) == 0;
}

/*
    print the line given to stdout
*/
void PrintLine(char* line, size_t index, void* context)
{
    printf("%s", line);
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


/**
    Recieve a line from a file if the line has a label on it add it to the programme
*/
void Assembler_SearchLabel(char* line, size_t index,void* ptr)
{
    char* word = NULL;
    Assembly* asmPtr = (Assembly*) ptr;
    Symbol symbol;
    if(!line || !asmPtr)
    {
        return;
    }

    /* spite to single words*/
    word = String_Split(line, SPACES_CH);


    if(Assembler_IsCodeLine(line))
    {
        asmPtr->lineCount++;
    }

    /* search for the label indicator in the file*/
    if(String_HasChar(line,LABEL_INDICATOR))
    {
        word = String_Split(line,LABEL_SPLITER);
        if(String_OnlyWithChars(word, LIGAL_LABEL_CH))
        {
            /* for now wont allow space between label and : wil correct in the future*/
            symbol = Symbol_Init(word, asmPtr->lineCount);
            SymbolTable_AddSymbol(&asmPtr->symbolTable, &symbol);
        }
    }

}


bool Assembler_AssembleFile(char* asmFile)
{
    Assembly assembly = Assembly_Init(asmFile);

    FILE* file = File_Open(asmFile, "r");
    if(!file)
    {
        Log(eError, "Could not open file");
        return false;
    }


    if(!File_ForEachLine(file, &Assembler_SearchLabel, &assembly))
    {
        Log(eError,"Could not read data from file");
        return false;
    }

    SymbolTable_Print(&assembly.symbolTable);

    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}







