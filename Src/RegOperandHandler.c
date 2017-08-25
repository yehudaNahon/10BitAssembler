#include "RegOperandHandler.h"
#include "RegOperandHandlerInternals.h"
#include "Convert.h"
#include "Operand.h"





Handler RegOperandHandler = {
    &RegOperandHandler_IsHandler,
    &RegOperandHandler_GetSize,
    &RegOperandHandler_Add,
};

bool RegOperandHandler_IsHandler(const char* param)
{
    return param[0] == REG_CH && Convert_StrToDecimal(&param[1]) < NUM_OF_REGS;
}

bool RegOperandHandler_Add(const char* operand,List* bytes,List symbols)
{
    OperandByte byte;
    if(!operand || !bytes || !RegOperandHandler_IsHandler(operand))
    {
        return false;
    }
    
    byte = OperandByte_Init(eRegister,Convert_StrToDecimal(&operand[1]));
    return List_Add(bytes,&byte, sizeof(OperandByte));
}

size_t RegOperandHandler_GetSize(const char* param)
{
    return 1;
}



