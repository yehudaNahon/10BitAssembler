#ifndef COMMAND_BYTE_H
#define COMMAND_BYTE_H

#include "Byte.h"

/* General for all commands in the assembly file*/
#define TYPE_BITS_NUM (2)

/* For First command byte*/
#define OPERAND_TYPE_BITS_NUM (2)
#define OPCODE_TYPE_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM - (OPERAND_TYPE_BITS_NUM * 2))

/* For all extra info byte of the command*/
#define OPERAND_VALUE_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM)
#define MAX_EXTRA_OPERANDS (2)

#define MAX_NUM_OF_ARGS (4)

#define TYPE_DEFAULT (0)


typedef struct CommandByte
{
    int opcode :OPCODE_TYPE_BITS_NUM;
    int srcOperand :OPERAND_TYPE_BITS_NUM;
    int destOperand :OPERAND_TYPE_BITS_NUM;
    int type :TYPE_BITS_NUM;
}CommandByte;

Byte CommandByte_Init(int opcode,int srcOp,int dstOp);

void CommandByte_PrintIter(const void* command,size_t len,void* context);


#endif