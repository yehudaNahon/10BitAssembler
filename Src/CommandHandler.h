#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "Handler.h"
#include "Assembly.h"


bool CommandHandler_IsLine(char* command);

size_t CommandHandler_GetLineSize(char* command, char* params);

size_t CommandHandler_Handle(char* command,char* params, Programme* prog);

void PrintCommandByteIter(const void* data,size_t len, void* context);

#endif