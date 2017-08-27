#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include "List.h"

#define MAX_COMMAND_STR_LEN (3)

typedef struct CommandOpcodes
{
    const const char* commandStr;
    int opcode;
}CommandOpcodes;

/*
    write the command to buffer till end or till len bytes

    return  :   true - sucess
                false - falied
*/
bool CommandUtils_GetCommand(const char* line,char* buffer, size_t len);

/*
    writes operands to the buffer till end or till len bytes

    return  :   true - sucess
            false - falied
*/
bool CommandUtils_GetOperands(const char* line,char* buffer, size_t len);

/*
    places a NULL char between the operand to create to seperate strings
    return  :   true - sucess
            false - falied
*/
char* CommandUtils_SplitOperands(char* operands,size_t len);

/*
    Returns the commands opcode

    command :   the command line (can have over chars but the command should start at index 0)
    commandOpcodes  :   a list of command opcodes by strings
    len : the length of the array

    return :    the command opcode on error -1
*/
int CommandUtils_GetOpcode(const char* command,const CommandOpcodes opcodeList[],size_t len);


/*
    parses the command to a command byte and add it to the byte list
    
    return  :   true - sucess
    false - falied
*/
bool CommandUtils_AddCommandByte(const char* command,const char* operands,const CommandOpcodes* opcodes, size_t len,List* bytes);


/*
    search in opcode list if one of the opcodes matches the command
    return  :  true - sucess
               false - falied
*/
bool CommandUtils_IsHandler(const char* commandStr,const CommandOpcodes opcodeList[],size_t len);



#endif