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

bool CommandUtils_GetCommand(const char* line,char* buffer, size_t len);

bool CommandUtils_GetOperands(const char* line,char* buffer, size_t len);

char* CommandUtils_SplitOperands(char* operands,size_t len);

int CommandUtils_GetOpcode(const char* command,const CommandOpcodes opcodeList[],size_t len);

bool CommandUtils_AddCommandByte(const char* command,const char* operands,const CommandOpcodes* opcodes, size_t len,List* bytes);

bool CommandUtils_IsHandler(const char* commandStr,const CommandOpcodes opcodeList[],size_t len);



#endif