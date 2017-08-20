#include "Assembly.h"
#include "Memory.h"
#include "String.h"

DataType DataType_Init()
{
    DataType type;
    type.symbol = SymbolTable_Init();
    type.memory = ByteTable_Init();
    type.counter = 0;

    return type;
}

Assembly Assembly_Init(char* fileName)
{
    Assembly assembly;

    /*copy file name*/
    Memory_Set(assembly.fileName,0,sizeof(assembly.fileName));
    Memory_Copy(assembly.fileName, fileName, String_Len(fileName));

    /*create sybol table*/
    assembly.data = DataType_Init();
    assembly.command = DataType_Init();

    assembly.commands = Queue_Init();

    return assembly;
}



