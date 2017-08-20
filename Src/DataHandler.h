#ifndef DATA_HANDLERS_H
#define DATA_HANDLERS_H

#include "Handler.h"


bool DataHandler_IsLine(char* command);

size_t DataHandler_AddLine(char* command,char* params, ByteTable* table);



#endif