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


Byte RegOperandByte_Init(int src,int dst)
{
    Byte byte;
    RegOperandByte* ptr = (RegOperandByte*)&byte;
    ptr->type = eAbsolute;
    ptr->src = src;
    ptr->dst = dst;

    return byte;
}

Byte OperandByte_Init(int type,int value)
{
    Byte byte;
    OperandByte* ptr = (OperandByte*)&byte;
    ptr->type = type;
    ptr->value = value;

    return byte;
}

EOperandType Operand_GetType(char* param)
{
    if(!param)
    {
        return eInvalid;
    }

    if(IsImmediate(param))
    {
        return eImmediate;
    }
    else if(IsMat(param))
    {
        return eMatAccess;   
    }
    else if(IsReg(param))
    {
        return eRegister;
    }
    else if(IsLabel(param))
    {
        return eLabel;   
    }

    return eInvalid;
}

size_t Operand_GetSize(EOperandType operand)
{
    switch(operand)
    {
        case eImmediate:
            return SizeImmediate();
        case eLabel:
            return SizeLabel();
        case eRegister:
            return SizeReg();
        case eMatAccess:
            return SizeMat();
        case eInvalid : 
            return 0;
        default:
            Log(eError, "recieved a unsported operandType");
            return 0;
    }
}

char* Operand_SplitOperands(char* operands)
{
    return String_SplitToTwo(operands,COMMA_CH);
}

size_t Operand_GetOperandsSize(EOperandType first,EOperandType second)
{
    if(first == eRegister && second == eRegister)
    {
        return 1;
    }

    return Operand_GetSize(first) + Operand_GetSize(second);
}

bool Operand_AddOperands(char* first,char* second,List* bytes,List symbols)
{
    EOperandType firstType,secondType;
    Byte byte,indexByte;
    bool answer = false;
    firstType = Operand_GetType(first);
    secondType = Operand_GetType(second);

    if(firstType == eRegister && secondType == eRegister)
    {
        return AddRegs(first,second,bytes);
    }

    if(first)
    {
        switch (firstType)
        {
            case eImmediate:
                answer = AddImmediate(first,bytes);
                break;
            case eLabel:
                answer = AddLabel(first,bytes,symbols);
                break;
            case eMatAccess:
                answer = AddMat(first,bytes,symbols);
                break;
            case eRegister:    
                answer = AddRegs(first,0,bytes);
                break;
            case eInvalid:
                return false;
        }
    }

    if(second)
    {
        switch (secondType)
        {
            case eImmediate:
                answer &= AddImmediate(second,bytes);
                break;
            case eLabel:
                answer &= AddLabel(second,bytes,symbols);
                break;
            case eMatAccess:
                answer &= AddMat(second,bytes,symbols);
                break;
            case eRegister:
                answer &= AddRegs(0,second,bytes);
                break;
            case eInvalid:
                return false;
        }
    }

    return answer;
}
