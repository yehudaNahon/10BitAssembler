#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "Handler.h"

bool CommandHandler_IsLine(char* command);

size_t CommandHandler_AddLine(char* command,char* params, ByteTable* table);


#endif