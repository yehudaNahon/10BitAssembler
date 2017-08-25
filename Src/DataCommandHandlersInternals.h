#ifndef DATA_COMMAND_HANDLERS_INTERNALS_H
#define DATA_COMMAND_HANDLERS_INTERNALS_H

#include "DataCommandHandlers.h"

#define STR_OPEN ('"')
#define STR_CLOSE ('"')

#define MAT_CLOSE ("]")
#define MAT_OPEN ('[')

#define COMMA_STR (",")

#define MAX_COMMAND_STR_LEN (20)

#define MAX_MAT_SIZE_STR_LEN (20)

#define MAX_MAT_PARAM_LEN (MAX_MAT_SIZE_STR_LEN + 100)

#define DATA_COMMAND_STR (".data")

#define STRING_COMMAND_STR (".string")

#define MAT_COMMAND_STR (".mat")



bool DataUtils_GetCommand(const char* line, char* buffer,size_t len);

char* DataUtils_GetParams(const char* line);

bool DataUtils_IsCommand(const char* line,const char* command);

bool StringCommandHandler_Add(const char* params, List* bytes,List symbols);

bool StringCommandHandler_IsHandler(const char* command);

size_t StringCommandHandler_GetSize(const char* params);

size_t MatCommandHandler_CalculateSize(const char* matStr);

bool MatCommandHandler_Add(const char* params,List* bytes,List symbols);

bool MatCommandHandler_IsHandler(const char* command);

size_t MatCommandHandler_GetSize(const char* params);

bool DataCommandHandler_IsHandler(const char* command);

size_t DataCommandHandler_GetSize(const char* params);

bool DataCommandHandler_Add(const char* params,List* bytes, List symbols);



#endif