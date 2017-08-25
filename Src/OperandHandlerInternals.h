#ifndef OPERAND_HANDLER_INTERNALS_H
#define OPERAND_HANDLER_INTERNALS_H

#include "OperandHandler.h"



bool OperandHandler_IsHandler(const char* commandStr);

size_t OperandHandler_GetSize(const char* commandStr);

bool OperandHandler_Add(const char* commandStr, List* bytes, List symbols);





#endif