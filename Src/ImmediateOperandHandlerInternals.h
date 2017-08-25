#ifndef IMMEDIATE_OPERAND_HANDLER_INTERNALS_H
#define IMMEDIATE_OPERAND_HANDLER_INTERNALS_H

#include "ImmediateOperandHandler.h"

#define IMMEDIATE_INDICATOR_CH ('#')

bool ImmediateOperandHandler_IsHandler(const char* param);

size_t ImmediateOperandHandler_GetSize(const char* param);

bool ImmediateOperandHandler_Add(const char* operand,List* bytes,List symbol);


#endif