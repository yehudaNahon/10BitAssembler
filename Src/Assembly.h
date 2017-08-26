#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "OSDefines.h"
#include "Queue.h"
#include "Segment.h"
#include "List.h"

#define MAX_LINE_LEN (800)

#define COMMA_STR (",")

typedef struct Programme
{
    Segment data;
    Segment code;
    List symbols;
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

void Assembly_Delete(Assembly* as);
#endif