#include "SymbolTable.h"
#include "OSDefines.h"

typedef struct Assembly
{
    char fileName[MAX_FILE_NAME];
    SymbolTable symbolTable;
    size_t lineCount;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init(char* fileName);

/*
    Copy a assembly file to a new one
*/
Assembly Assembly_Copy(Assembly* other);








