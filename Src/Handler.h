#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stddef.h>
#include <stdbool.h>


typedef size_t (*Action) (char*,char*,void*);

typedef struct Handler
{
    const char* command;
    Action act;

}Handler;

size_t Handler_Handle(char* command,char* params, void* context, Handler handlers[], size_t numOfElements);

bool Handler_HasHandler(char* command,Handler handlers[], size_t numOfElements);


#endif