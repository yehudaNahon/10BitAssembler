#include "Convert.h"
#include "ImmediateOperandHandler.h"
#include "ImmediateOperandHandlerInternals.h"
#include "String.h"
#include "Operand.h"
#include <stdio.h>

int Immediate_GetValue(const char* immediateStr)
{
    if(!immediateStr)
    {
        return 0;
    }
    return Convert_StrToDecimal(&immediateStr[1]);
}

bool IsImmediate(const char* param)
{
    if(!param || param[0] != IMMEDIATE_INDICATOR_CH || !String_IsNumber(&param[1]))
    {
        return false;
    }
    return true;
}

size_t SizeImmediate()
{
    return 1;
}

bool AddImmediate(const char* operand,List* bytes)
{
    Byte byte;
    if(!operand || !bytes || !IsImmediate(operand))
    {
        return false;
    }
    byte = OperandByte_Init(eAbsolute,Convert_StrToDecimal(&operand[1]));
    return Byte_Add(byte,bytes);
}

