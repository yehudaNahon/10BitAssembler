#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stddef.h>
#include <stdbool.h>

#include "List.h"


/*
    This is a interface for line handlers in the entire system 
    each "handler" needs to give this 3 given functions to the struct:
    IsHandler - a function to ask if the given handler can handle the line
                given 
                true - this is the right handler
                false - im not right for this job
    GetSize   - becuse the handling function will most likly add to the bytes
                list in the handler function this function will predict how many 
                elements it would add to the list and by that will enable the user
                to better handle the handler
    Add       - this is the handling function it gets the line to handle and 2 lists 
                to write the outcome to

    note :  if you have watched the operands parsers you probobly asked yourself why 
            arent they handlers? so they were sposed to but becuse of the register handler witch
            acts wierd with the size and parsing they could not have been so i tried to keep them 
            as much uniformed as possible to the handlers but they do not keep the pretty incapsulation 
            of the handlers interface
*/
typedef struct Handler
{
    bool (*IsHandler) (const char* line);
    size_t (*GetSize) (const char* line);
    bool (*Add) (const char* line,List* bytes,List* symbols);
}Handler;

/*
    gets a list of handlers and ask each one of them if he is can handle
    the data if it found a match will return true, false else

    command - the command to handle
    handlers - an array of handlers
    numOfElements - the number of handlers

    true - success 
    false -else
*/
bool Handler_HasHandler(const char* command,Handler handlers[], size_t numOfElements);

/*
    return the matching handlers from the list NULL if no handler was found
*/
Handler* Handler_GetHandler(const char* command,Handler Handler_Init[],size_t len);

/*
    a iterator object to find a handlers in a container
    will get the handler as data and the quary question as context
*/
bool Handler_Finder(void* handlerPtr,size_t len,void* context);

#endif