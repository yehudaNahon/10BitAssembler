#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "OSDefines.h"
#include "Queue.h"
#include "Segment.h"
#include "List.h"

/* the maximum number of characters in a assembly line*/
#define MAX_LINE_LEN (800)

/*
    a programme data strcuture
*/
typedef struct Programme
{
    Segment data;
    Segment code;
    List symbols;
    size_t errorCount;
}Programme;

/*
    a ssembly data structure used for creating and working with the assembly file
*/
typedef struct Assembly
{
    Programme prog;    
    Queue penndingCommands;
}Assembly;

/*
    Initialize a new Assembly data structure
*/
Assembly Assembly_Init();

/*
    Creates a new programme
*/
Programme Programme_Init(); 

/*
    notify that the assembler has incauntered a problem 
    during the assembly process
*/
void NotifyError(Programme* prog);

/*
    free asembly resources
*/
void Assembly_Delete(Assembly* as);


#endif