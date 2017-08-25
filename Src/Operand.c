#include "Operand.h"
#include "CommandHandler.h"
#include "Convert.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>
#include "Memory.h"
#include "MatOperandHandler.h"
#include "LabelOperandHandler.h"
#include "RegOperandHandler.h"
#include "ImmediateOperandHandler.h"


OperandByte OperandByte_Init(int type,int value)
{
    OperandByte byte;

    byte.type = type;
    byte.value = value;

    return byte;
}

EOperandType Operand_GetType(char* param)
{
    if(!param)
    {
        return eInvalid;
    }

    if(ImmediateOperandHandler.IsHandler(param))
    {
        return eImmediate;
    }
    else if(MatOperandHandler.IsHandler(param))
    {
        return eMetAccess;   
    }
    else if(RegOperandHandler.IsHandler(param))
    {
        return eRegister;
    }
    else if(LabelOperandHandler.IsHandler(param))
    {
        return eLabel;   
    }

    return eInvalid;
}

size_t Operand_GetSize(char* operandStr)
{
    switch(Operand_GetType(operandStr))
    {
        
        case eImmediate:
        case eLabel:
        case eMetAccess:
        case eRegister:
            return 1;
        case eInvalid : 
            return 0;
        default:
            Log(eError, "recieved a unsported operandType");
            return 0;
    }
}


bool Operand_Add(char* operandStr,List* bytes, List symbols)
{
    switch(Operand_GetType(operandStr))
    {
        case eImmediate:
            return ImmediateOperandHandler.Add(operandStr, bytes,symbols);
        case eLabel:
            return LabelOperandHandler.Add(operandStr, bytes, symbols);
        case eMetAccess:
            return MatOperandHandler.Add(operandStr, bytes, symbols); 
        case eRegister:
            return RegOperandHandler.Add(operandStr, bytes,symbols);
        case eInvalid : 
            break;
        default:
            Log(eError, "recieved a unsported operandType");
    }
    return false;
}


