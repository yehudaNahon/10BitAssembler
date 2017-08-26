#ifndef COMMAND_HANDLER_INTERNALS_H
#define COMMAND_HANDLER_INTERNALS_H

#include "CommandHandler.h"
#include "CommandByte.h"
#include "Operand.h"


bool CommandHandler_Add(const char* command,List* byte,List* symbols);

size_t CommandHandler_GetSize(const char* command);

bool CommandHandler_IsCommand(const char* command);

#endif