#ifndef REG_OPERAND_HANDLER_H
#define REG_OPERAND_HANDLER_H

#include "Handler.h"

extern Handler RegOperandHandler;

/*
    returns wether or not the operand is a register or not
*/
bool IsReg(const char* reg);

/*
    adds the register to the list
*/
bool AddRegs(const char* reg1,const char* reg2,List* bytes);

/*
    returns the register operand length
*/
size_t SizeReg();


#endif