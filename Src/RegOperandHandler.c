#include "RegOperandHandler.h"
#include "Convert.h"
#include "Operand.h"
#include "BitArray.h"
#include <stdio.h>


#define REG_CH ('r')
#define NUM_OF_REGS (8)


int Reg_GetValue(const char* regStr)
{
    if(!regStr)
    {
        return -1;
    }
    return Convert_StrToDecimal(&regStr[1]);
}

bool IsReg(const char* param)
{
    return param[0] == REG_CH && Convert_StrToDecimal(&param[1]) < NUM_OF_REGS;
}

bool AddRegs(const char* reg1,const char* reg2,List* bytes)
{
    Byte byte;
    int val1 = 0,val2 = 0;
    
    if(!bytes)
    {
        return false;
    }
    
    if(reg1 && IsReg(reg1))
    {
        val1 = Convert_StrToDecimal(&reg1[1]);
    }

    if(reg2 && IsReg(reg2))
    {
        val2 = Convert_StrToDecimal(&reg2[1]);
    }

    byte = RegOperandByte_Init(val1,val2);
    return Byte_Add(byte,bytes);
}


size_t SizeReg()
{
    return 1;
}



