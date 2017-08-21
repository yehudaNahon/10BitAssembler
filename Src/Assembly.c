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
    assembly.data = Segment_Init();
    assembly.command = Segment_Init();
    assembly.symbol = SymbolTable_Init();
    
    assembly.penndingCommands = Queue_Init();

    return assembly;
}



