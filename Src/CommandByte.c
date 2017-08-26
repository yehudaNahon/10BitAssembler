#include "CommandByte.h"
#include "Operand.h"
#include <stdio.h>
#include "BitArray.h"

#define STR(x) #x

CommandByte CommandByte_Init(int opcode,int srcOp,int dstOp)
{
    CommandByte byte;
    
    byte.opcode = opcode;
    byte.destOperand = dstOp;
    byte.srcOperand = srcOp;
    byte.type = eAbsolute;

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
