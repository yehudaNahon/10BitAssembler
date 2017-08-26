#ifndef REG_OPERAND_HANDLER_H
#define REG_OPERAND_HANDLER_H

#include "Handler.h"

extern Handler RegOperandHandler;


bool IsReg(const char* reg);

bool AddRegs(const char* reg1,const char* reg2,List* bytes);

size_t SizeReg();


#endif