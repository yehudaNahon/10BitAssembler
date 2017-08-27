#ifndef OPERAND_H
#define OPERAND_H

#include "Assembly.h"
#include "CommandByte.h"
#include <stddef.h>
#include <stdbool.h>

#define OPERAND_DEFAULT (0)

/*
    this is a enum for all operand types
*/
typedef enum EOperandType
{
    eImmediate,
    eLabel,
    eMatAccess,
    eRegister,
    eInvalid
}EOperandType;

/*
    a mepping of the operand byte in a programmes byte
*/
typedef struct OperandByte
{
    int type :TYPE_BITS_NUM;
    int value :OPERAND_VALUE_BITS_NUM;
}OperandByte;

/*
    a mapping of a register operand byte in a programmes byte
*/
#define REG_OPERAND_BITS_NUM (4)
typedef struct RegOperandByte
{
    int type : TYPE_BITS_NUM;
    int dst : REG_OPERAND_BITS_NUM;
    int src : REG_OPERAND_BITS_NUM;
}RegOperandByte;

/*
    Initialize the register byte
*/
Byte RegOperandByte_Init(int src,int dst);


/*
    Initialize the operand byte
*/
Byte OperandByte_Init(int type,int value);


/*
    return the operands type
*/
EOperandType Operand_GetType(char* param);

/*
    returns the operands size by type
*/
size_t Operand_GetSize(EOperandType operand);

/*
    adds the operand to the list
*/
bool Operand_Add(char* operandStr, List* bytes, List* symbols);

/*
    returns the operands size
*/
size_t Operand_GetOperandsSize(EOperandType first,EOperandType second);

/*
    adds the operands to the byte list
    note :  this function is usefull even if one of the operands is NULL it will determing 
            the reaction accordinly
*/
bool Operand_AddOperands(char* first,char* second,List* bytes,List* symbols);

/*
    split the stirng of the operands to 2 string and return the one not in the base
    note : the 2 will be seperated in the same buffer with a NULL char
*/
char* Operand_SplitOperands(char* operands);

#endif
