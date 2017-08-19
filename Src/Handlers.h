#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "Handler.h"


bool CommandHandler_IsCommandLine(char* line);

size_t CommandHandler_AddCommandLine(char* line,LinkedList* list);

bool DataHandler_IsDataLine(char* line);

size_t DataHandler_AddDataLine(char* line,LinkedList* list);


#endif