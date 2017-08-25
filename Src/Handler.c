#include <stdio.h>
#include "Handler.h"
#include "String.h"

bool Handler_HasHandler(const char* command,Handler handlerList[], size_t numOfElements)
{
    return Handler_GetHandler(command,handlerList,numOfElements);
}

Handler* Handler_GetHandler(const char* command,Handler handlerList[],size_t len)
{
    size_t i = 0;
    
    for(i = 0; i< len ; i++)
    {
        if(handlerList[i].IsHandler(command))
        {
            return &handlerList[i];
        }
    }

    return NULL;
}



bool Handler_Finder(void* handlerPtr,size_t len,void* context)
{
    Handler* handler = handlerPtr;
    if(handler->IsHandler(context))
    {
        return true;
    }

    return false;
}