#ifndef REG_OPERAND_HANDLER_INTERNALS_H
#define REG_OPERAND_HANDLER_INTERNALS_H

#include "RegOperandHandler.h"

#define REG_CH ('r')
#define NUM_OF_REGS (8)


bool RegOperandHandler_IsHandler(const char* param);

size_t RegOperandHandler_GetSize(const char* param);

bool RegOperandHandler_Add(const char* operand,List* bytes,List symbols);







#endif