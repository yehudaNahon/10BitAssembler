#ifndef DATA_HANDLERS_H
#define DATA_HANDLERS_H

#include "Handler.h"
#include "ByteTable.h"

bool DataHandler_IsLine(char* command);

size_t DataHandler_Handle(char* command,char* params, ByteTable* table);



#endif