#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "Handler.h"
#include "Assembly.h"


bool CommandHandler_IsLine(char* command);

size_t CommandHandler_GetLineSize(char* command);

size_t CommandHandler_Handle(char* command,char* params, Programme* prog);

#endif