#ifndef OPERAND_H
#define OPERAND_H

#include <stddef.h>
#include <stdbool.h>
#include "Assembly.h"
#include "CommandByte.h"

#define OPERAND_DEFAULT (0)


typedef enum EOperandType
{
    eImmediate,
    eDirect,
    eMetAccess,
    eDirectRegister,
    eInvalid
}EOperandType;


typedef struct OperandByte
{
    int type :TYPE_BITS_NUM;
    int value :OPERAND_VALUE_BITS_NUM;
}OperandByte;

bool BuildOperandByte(char* operand,Programme* prog,OperandByte* byte);

EOperandType GetOperandType(char* param);

size_t GetOperandSize(char* operandStr);

bool IsImmediate(char* param);
bool IsLabel(char* param);
bool IsRegAccess(char* param);


#endif