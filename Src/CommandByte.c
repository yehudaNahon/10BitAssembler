#include "CommandByte.h"



CommandByte CommandByte_Init(int opcode,int srcOp,int dstOp)
{
    CommandByte byte;
    
    byte.opcode = opcode;
    byte.destOperand = dstOp;
    byte.srcOperand = srcOp;
    byte.type = eAbsolute;

    return byte;
}


