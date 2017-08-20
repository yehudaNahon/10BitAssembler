
#include "CommandHandler.h"
#include "CommandHandlerInternals.h"
#include "String.h"


size_t Handle_mov(char* command, void* context)
{
    return 1;    
}

size_t Handle_cmp(char* command, void* context)
{
    return 1;        
}

size_t Handle_add(char* command, void* context)
{
    return 1;
}

size_t Handle_sub(char* command, void* context)
{
    return 1;
}

size_t Handle_not(char* command, void* context)
{
    return 1;
}

size_t Handle_clr(char* command, void* context)
{
    return 1;
}

size_t Handle_lea(char* command, void* context)
{
    return 1;
}

size_t Handle_inc(char* command, void* context)
{
    return 1;
}

size_t Handle_dec(char* command, void* context)
{
    return 1;
}

size_t Handle_jmp(char* command, void* context)
{
    return 1;
}

size_t Handle_bne(char* command, void* context)
{
    return 1;
}

size_t Handle_red(char* command, void* context)
{
    return 1;
}

size_t Handle_prn(char* command, void* context)
{
    return 1;
}

size_t Handle_jsr(char* command, void* context)
{
    return 1;
}

size_t Handle_rts(char* command, void* context)
{
    return 1;
}

size_t Handle_stop(char* command, void* context)
{
    return 1;
}

#define COMMAND_NUM_OF_ELEM (16)
Handler commandHandlers[COMMAND_NUM_OF_ELEM] = {
    {"mov",&Handle_mov},
    {"cmp",&Handle_cmp},
    {"add",&Handle_add},
    {"sub",&Handle_sub},
    {"not",&Handle_not},
    {"clr",&Handle_clr},
    {"lea",&Handle_lea},
    {"inc",&Handle_inc},
    {"dec",&Handle_dec},
    {"jmp",&Handle_jmp},
    {"bne",&Handle_bne},
    {"red",&Handle_red},
    {"prn",&Handle_prn},
    {"jsr",&Handle_jsr},
    {"rts",&Handle_rts},
    {"stop",&Handle_stop}
};

CommandType commandTypes[COMMAND_NUM_OF_ELEM] = {
    {"mov",eTwoOperands},
    {"cmp",eTwoOperands},
    {"add",eTwoOperands},
    {"sub",eTwoOperands},
    {"not",eSingleOperand},
    {"clr",eSingleOperand},
    {"lea",eTwoOperands},
    {"inc",eSingleOperand},
    {"dec",eSingleOperand},
    {"jmp",eSingleOperand},
    {"bne",eSingleOperand},
    {"red",eSingleOperand},
    {"prn",eSingleOperand},
    {"jsr",eSingleOperand},
    {"rts",eNoOperand},
    {"stop",eNoOperand}
};




bool CommandHandler_IsLine(char* command)
{
    return Handler_IsInList(command, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_AddLine(char* command, char* params, ByteTable* table)
{
    return Handler_AddLine(command, params, table, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_GetLineSize(char* command)
{
    int i=0;
    
        for(i=0;i< COMMAND_NUM_OF_ELEM ; i++)
        {        
            /*return true only if the strings are the same from the start*/
            if(String_Compare(command, commandTypes[i].command, String_Len(commandTypes[i].command)) == 0)
            {
                return (size_t)commandTypes[i].type;
            }
        } 
        return 0;
}



