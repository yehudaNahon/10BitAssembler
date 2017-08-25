#ifndef OPERAND_H
#define OPERAND_H

#include "Assembly.h"
#include "CommandByte.h"
#include <stddef.h>
#include <stdbool.h>

#define OPERAND_DEFAULT (0)

typedef enum EOperandType
{
    eImmediate,
    eLabel,
    eMetAccess,
    eRegister,
    eInvalid
}EOperandType;


typedef struct OperandByte
{
    int type :TYPE_BITS_NUM;
    int value :OPERAND_VALUE_BITS_NUM;
}OperandByte;


OperandByte OperandByte_Init(int type,int value);

EOperandType Operand_GetType(char* param);

size_t Operand_GetSize(char* operandStr);

bool Operand_Add(char* operandStr, List* bytes, List symbols);


#endif
