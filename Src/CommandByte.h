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


/* a programmes command byte*/
typedef struct CommandByte
{
    int type :TYPE_BITS_NUM;                    /*the encoding type (ERA)*/
    int destOperand :OPERAND_TYPE_BITS_NUM;     /* the destination operands type*/
    int srcOperand :OPERAND_TYPE_BITS_NUM;      /* the source operands type*/
    int opcode :OPCODE_TYPE_BITS_NUM;           /* the commands opcode*/
}CommandByte;

/*
    Initialize a new command byte
*/
Byte CommandByte_Init(int opcode,int srcOp,int dstOp);

/*
    a iterator for printing all command bytes values
*/
void CommandByte_PrintIter(const void* command,size_t len,void* context);


#endif