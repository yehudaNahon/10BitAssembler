#include "SymbolTable.h"
#include "OSDefines.h"
#include "Queue.h"

typedef struct Assembly
{
    char fileName[MAX_FILE_NAME];
    SymbolTable codeSymbols;
    SymbolTable dataSymbols;
    size_t instructionCounter;
    size_t dataCounter;
    Queue commands;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init(char* fileName);

void Assembly_ResetLineCount(Assembly* as);





