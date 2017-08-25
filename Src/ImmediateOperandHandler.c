#include "Convert.h"
#include "ImmediateOperandHandler.h"
#include "ImmediateOperandHandlerInternals.h"
#include "String.h"
#include "Operand.h"

Handler ImmediateOperandHandler = {
    &ImmediateOperandHandler_IsHandler,
    &ImmediateOperandHandler_GetSize,
    &ImmediateOperandHandler_Add,
};


bool ImmediateOperandHandler_IsHandler(const char* param)
{
    if(!param || param[0] != IMMEDIATE_INDICATOR_CH || !String_IsNumber(&param[1]))
    {
        return false;
    }

    return true;
}

size_t ImmediateOperandHandler_GetSize(const char* param)
{
    return 1;
}

bool ImmediateOperandHandler_Add(const char* operand,List* bytes,List symbol)
{
    OperandByte byte;
    if(!operand || !bytes || ImmediateOperandHandler_IsHandler(operand))
    {
        return false;
    }

    byte = OperandByte_Init(eImmediate,Convert_StrToDecimal(&operand[1]));
    return List_Add(bytes,&byte, sizeof(OperandByte));
}

