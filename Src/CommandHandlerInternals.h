#ifndef COMMAND_HANDLER_INTERNALS_H
#define COMMAND_HANDLER_INTERNALS_H

#include "CommandHandler.h"

/* General for all commands in the assembly file*/
#define TYPE_BITS_NUM (2)

/* For First command byte*/
#define OPERAND_TYPE_BITS_NUM (2)
#define OPCODE_TYPE_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM - (OPERAND_TYPE_BITS_NUM * 2))

/* For all extra info byte of the command*/
#define OPERAND_VALUE_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM)
#define MAX_EXTRA_OPERANDS (2)

#define MAX_NUM_OF_ARGS (4)

typedef enum ECommandType
{
    eNoOperand,
    eSingleOperand,
    eTwoOperands
}ECommandType;

typedef enum EEncodingType
{
    eAbsolute,
    eExternal,
    eRelocatable
}EEncodingType;

typedef enum EAddressingType
{
    eImmediate,
    eDirect,
    eMetAccess,
    eDirectRegister,
    eInvalid
}EAddressingType;

typedef struct CommandType
{
    const char* command;
    ECommandType type;
}CommandType;

typedef struct CommandByte
{
    int type :TYPE_BITS_NUM;
    int destOperand :OPERAND_TYPE_BITS_NUM;
    int srcOperand :OPERAND_TYPE_BITS_NUM;
    int opcode :OPCODE_TYPE_BITS_NUM;
}CommandByte;

typedef struct OperandByte
{
    int type :TYPE_BITS_NUM;
    int value :OPERAND_VALUE_BITS_NUM;
}OperandByte;

typedef struct Operand
{
    EAddressingType type;
    size_t len;
    OperandByte bytes[MAX_NUM_OF_ARGS];
}Operand;

typedef struct Command
{
    CommandByte command;
    size_t numOfOperands;
    OperandByte extraInfo[MAX_NUM_OF_ARGS];
}Command;


#endif