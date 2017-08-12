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
    assembly.lineCount = 0;

    return assembly;
}


Assembly Assembly_Copy(Assembly* other)
{
    Assembly this = Assembly_Init(other->fileName);
    
    this.symbolTable = SymbolTable_Copy(&other->symbolTable);
    this.lineCount = other->lineCount;

    return this;
}



