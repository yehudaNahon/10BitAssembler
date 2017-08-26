#include "CommandByte.h"
#include "Operand.h"
#include <stdio.h>
#include "BitArray.h"

#define STR(x) #x

Byte CommandByte_Init(int opcode,int srcOp,int dstOp)
{
    Byte byte;
    CommandByte* ptr = (CommandByte*) &byte;

    ptr->opcode = opcode;
    ptr->destOperand = dstOp;
    ptr->srcOperand = srcOp;
    ptr->type = eAbsolute;

    return byte;
}

void CommandByte_PrintIter(const void* command,size_t len,void* context)
{
    const CommandByte* byte = command;

    if(command && byte->type == eAbsolute)
    {    
        printf("%d :: %d -> %d\n",byte->opcode,byte->srcOperand,byte->destOperand);
    }
}
