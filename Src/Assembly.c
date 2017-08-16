#include "Assembly.h"
#include "Memory.h"
#include "String.h"

Assembly Assembly_Init(char* fileName)
{
    Assembly assembly;

    /*copy file name*/
    Memory_Set(assembly.fileName,0,sizeof(assembly.fileName));
    Memory_Copy(assembly.fileName, fileName, String_Len(fileName));

    /*create sybol table*/
    assembly.symbolTable = SymbolTable_Init();
    assembly.instructionCounter = 0;
    assembly.dataCounter = 0;

    assembly.commands = Queue_Init();

    return assembly;
}

void Assembly_ResetLineCount(Assembly* as)
{
}


