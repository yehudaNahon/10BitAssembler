#include "SymbolTable.h"
#include "OSDefines.h"
#include "Queue.h"
#include "ByteTable.h"

typedef struct DataType
{
    SymbolTable symbol;
    ByteTable memory;
    size_t counter;
}DataType;


typedef struct Assembly
{
    char fileName[MAX_FILE_NAME];
    DataType data;
    DataType command;
    Queue commands;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init(char* fileName);





