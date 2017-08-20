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

bool Handler_AddLine(char* line, ByteTable* table, Handler handlers[], size_t numOfElements);

bool Handler_IsInList(char* line,Handler handlers[], size_t numOfElements);


#endif