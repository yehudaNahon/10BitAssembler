#include "OSDefines.h"
#include "Queue.h"
#include "Segment.h"

typedef struct Assembly
{
    char fileName[MAX_FILE_NAME];
    Segment data;
    Segment command;
    SymbolTable symbol;    
    Queue penndingCommands;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init(char* fileName);





