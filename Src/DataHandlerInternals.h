#ifndef DATA_HANDLER_INTERNALS_H
#define DATA_HANDLER_INTERNALS_H

#include "DataHandler.h"



bool DataHandler_IsHandler(const char* data);

size_t DataHandler_GetSize(const char* data);

bool DataHandler_Add(const char* data, List* bytes,List symbols);








#endif