
#include <stdint.h>
#include <stddef.h>

/* General for all bytes in the assembly file*/
#define BYTE_LEN (10)

/* General for all commands in the assembly file*/
#define TYPE_BITS_NUM (2)

/* For First command byte*/
#define OPERAND_TYPE_BITS_NUM (2)
#define OPCODE_TYPE_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM - (OPERAND_TYPE_BITS_NUM * 2))

/* For all extra info byte of the command*/
#define OPERAND_ADDRESS_BITS_NUM (BYTE_LEN - TYPE_BITS_NUM)
#define MAX_EXTRA_OPERANDS (2)

typedef struct Byte
{
    int value :BYTE_LEN;
}Byte;


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
    eDirectRegister
}EAddressingType;

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
    int address :OPERAND_ADDRESS_BITS_NUM;
}OperandByte;

typedef struct Command
{
    size_t numOfOperands;
    CommandByte command;
    OperandByte exraInfo[MAX_EXTRA_OPERANDS];
}Command;











