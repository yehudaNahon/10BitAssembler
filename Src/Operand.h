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
    eMatAccess,
    eRegister,
    eInvalid
}EOperandType;


typedef struct OperandByte
{
    int type :TYPE_BITS_NUM;
    int value :OPERAND_VALUE_BITS_NUM;
}OperandByte;

#define REG_OPERAND_BITS_NUM (4)
typedef struct RegOperandByte
{
    int type : TYPE_BITS_NUM;
    int src : REG_OPERAND_BITS_NUM;
    int dst : REG_OPERAND_BITS_NUM;
}RegOperandByte;

Byte RegOperandByte_Init(int src,int dst);

Byte OperandByte_Init(int type,int value);

EOperandType Operand_GetType(char* param);

size_t Operand_GetSize(EOperandType operand);

bool Operand_Add(char* operandStr, List* bytes, List symbols);

size_t Operand_GetOperandsSize(EOperandType first,EOperandType second);

bool Operand_AddOperands(char* first,char* second,List* bytes,List symbols);

char* Operand_SplitOperands(char* operands);

#endif
