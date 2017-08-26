#ifndef COMMAND_TYPE_HANDLER_INTERNALS_H
#define COMMAND_TYPE_HANDLER_INTERNALS_H

#include "CommandTypeHandlers.h"

bool NoOperandHandler_Add(const char* commandStr,List* bytes,List* symbols);

size_t NoOperandHandler_GetSize(const char* commandStr);

bool NoOperandHandler_IsHandler(const char* commandStr);

bool SingleOperandHandler_Add(const char* commandStr,List* bytes,List* symbols);

size_t SingleOperandHandler_GetSize(const char* commandStr);

bool SingleOperandHandler_IsHandler(const char* commandStr);

bool TwoOperandsHandler_Add(const char* commandStr,List* bytes,List* symbols);

size_t TwoOperandsHandler_GetSize(const char* commandStr);

bool TwoOperandsHandler_IsHandler(const char* commandStr);




#endif