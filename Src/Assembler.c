#include "Assembler.h"
#include "AssemblerInner.h"
#include "Log.h"
#include "FileUtils.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>


#define MAX_SYMBOL_NAME_LEN (80)
/*
    A data structure containing a single symbol each symbol is represented by a name and 
    linked into an address in memory
*/
typedef struct Symbol
{
    char name[80];
    uint32_t address;
}Symbol; 

/**
    The Symbol Table Contains all the symbols in an assembly file
*/
typedef struct SymbolTable
{
    size_t count;
    Symbol *symbols;
}SymbolTable;



bool IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = FindTypeSplitCharacter(fileName);
	
	return ptr == NULL || strcmp(ptr,ASSEMBLY_END) == 0;
}


void PrintLine(char* line, size_t index, void* context)
{
    printf("%lu :: %s",index, line);
}

bool AssembleFile(char* AssemblerFile)
{
    FILE* file = fopen(AssemblerFile, "r");
    if(!file)
    {
        Log(eError, "Could not open file");
        return false;
    }


    if(!ForEachLine(file, &PrintLine, NULL))
    {
        Log(eError,"Could not read data from file");
        return false;
    }

    if(fclose(file) == EOF)
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}


