#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stddef.h>
#include <stdbool.h>
#include "ByteTable.h"


typedef size_t (*Action) (char*,void*);

typedef struct Handler
{
    const char* command;
    Action act;

}Handler;

size_t Handler_AddLine(char* command,char* params, ByteTable* table, Handler handlers[], size_t numOfElements);

bool Handler_IsInList(char* command,Handler handlers[], size_t numOfElements);


#endif