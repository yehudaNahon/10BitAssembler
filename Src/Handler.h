#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stddef.h>
#include <stdbool.h>

#include "List.h"



typedef struct Handler
{
    bool (*IsHandler) (const char* line);
    size_t (*GetSize) (const char* line);
    bool (*Add) (const char* line,List* bytes,List* symbols);
}Handler;

bool Handler_HasHandler(const char* command,Handler handlers[], size_t numOfElements);

Handler* Handler_GetHandler(const char* command,Handler Handler_Init[],size_t len);

bool Handler_Finder(void* handlerPtr,size_t len,void* context);

#endif