#include <stdio.h>
#include "Handler.h"
#include "String.h"

bool Handler_HasHandler(char* command,Handler handlers[], size_t numOfElements)
{
    int i=0;
    for(i=0;i< numOfElements ; i++)
    {
        /*return true only if the strings are the same from the start*/
        if(!String_Compare(command, handlers[i].command, String_Len(handlers[i].command)))
        {
            return true;
        }
    } 

    return false;
}

size_t Handler_Handle(char* command,char* params, void* context, Handler handlers[], size_t numOfElements)
{
    int i=0;
    for(i=0;i< numOfElements ; i++)
    {        
        /*return true only if the strings are the same from the start*/
        if(String_Compare(command, handlers[i].command, String_Len(handlers[i].command)) == 0)
        {
            return handlers[i].act(command, params, context);
        }
    } 
    return 0;
}
