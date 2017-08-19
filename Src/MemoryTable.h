
#include <stdint.h>
#include <stddef.h>

/* General for all words in the assembly file*/
#define WORD_LEN (10)

/* General for all commands in the assembly file*/
#define TYPE_BITS_NUM (2)

/* For First command word*/
#define OPERAND_TYPE_BITS_NUM (2)
#define OPCODE_TYPE_BITS_NUM (WORD_LEN - TYPE_BITS_NUM - (OPERAND_TYPE_BITS_NUM * 2))

/* For all extra info word of the command*/
#define OPERAND_ADDRESS_BITS_NUM (WORD_LEN - TYPE_BITS_NUM)
#define MAX_EXTRA_OPERANDS (2)

typedef struct Word
{
    uint16_t size :WORD_LEN;
}Word;


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

typedef struct CommandWord
{
    uint8_t type :TYPE_BITS_NUM;
    uint8_t destOperand :OPERAND_TYPE_BITS_NUM;
    uint8_t srcOperand :OPERAND_TYPE_BITS_NUM;
    uint8_t opcode :OPCODE_TYPE_BITS_NUM;
}CommandWord;

typedef struct OperandWord
{
    uint8_t type :TYPE_BITS_NUM;
    uint8_t address :OPERAND_ADDRESS_BITS_NUM;
}OperandWord;

typedef struct DataWord
{
    uint16_t value :WORD_LEN;
}DataWord;


typedef struct Command
{
    size_t numOfOperands;
    CommandWord command;
    OperandWord exraInfo[MAX_EXTRA_OPERANDS];
}Command;











