#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stddef.h>

typedef size_t (*Action) (char*,void*);

typedef struct Handler
{
    const char* command;
    Action act;

}Handler;

#endif