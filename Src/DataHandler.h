#ifndef DATA_HANDLERS_H
#define DATA_HANDLERS_H

#include "Handler.h"
#include "ByteTable.h"
#include "List.h"

bool DataHandler_IsLine(char* command);

size_t DataHandler_Handle(char* command,char* params, List* bytes);



#endif