#include "OSDefines.h"
#include "Queue.h"
#include "Segment.h"

typedef struct Programme
{
    Segment data;
    Segment code;
    SymbolTable symbol;
}Programme;

typedef struct Assembly
{
    char fileName[MAX_FILE_NAME];
    Programme prog;    
    Queue penndingCommands;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init(char* fileName);

Programme Programme_Init(); 



