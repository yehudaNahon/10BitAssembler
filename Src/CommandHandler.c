#include "Convert.h"
#include "CommandHandler.h"
#include "CommandHandlerInternals.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>

size_t Handle_NoOperandCommand(char* command, char* params,void* context);
size_t Handle_SingleOperandCommands(char* command,char* params,void* context);
size_t Handle_TwoOperandCommands(char* command, char* params, void* context);

#define COMMAND_NUM_OF_ELEM (16)
Handler commandHandlers[COMMAND_NUM_OF_ELEM] = {
    {"mov",&Handle_TwoOperandCommands},
    {"cmp",&Handle_TwoOperandCommands},
    {"add",&Handle_TwoOperandCommands},
    {"sub",&Handle_TwoOperandCommands},
    {"not",&Handle_SingleOperandCommands},
    {"clr",&Handle_SingleOperandCommands},
    {"lea",&Handle_TwoOperandCommands},
    {"inc",&Handle_SingleOperandCommands},
    {"dec",&Handle_SingleOperandCommands},
    {"jmp",&Handle_SingleOperandCommands},
    {"bne",&Handle_SingleOperandCommands},
    {"red",&Handle_SingleOperandCommands},
    {"prn",&Handle_SingleOperandCommands},
    {"jsr",&Handle_SingleOperandCommands},
    {"rts",&Handle_NoOperandCommand},
    {"stop",&Handle_NoOperandCommand}
};

void Operand_SetValue(OperandByte* op, int value)
{
    op->value = value;
}

#define DIRECT_CH ('#')
bool IsImmediate(char* param)
{
    return param[0] == DIRECT_CH;
}

bool IsLabel(char* param,List symbols)
{
    void* ptr = NULL;
    return List_FindData(symbols, ptr, &Symbol_Finder, param) != 0;
}

#define REG_CH ('r')
bool IsRegAccess(char* param)
{
    return param[0] == REG_CH && Convert_StrToDecimal(&param[1]) < NUM_OF_REGS;
}

bool IsMatAccess(char* param,List symbols)
{
    char buffer[MAX_LINE_LEN];
    char* ptr = NULL;
    char* mat = NULL;

    /* validaty check*/
    if(!param)
    {
        return false;
    }

    String_Copy(buffer, param, MAX_LINE_LEN);

    
    /* locate the mat []*/
    mat = String_SplitToTwo(buffer, MAT_OPEN);
    if(!mat)
    {
        return false;
    }
    
    /*check the place is a valid label*/
    if(!IsLabel(buffer,symbols))
    {
        return false;
    }
    
    /* check all mat params are valid registers*/
    ptr = String_Split(mat, MAT_CLOSE);
    do
    {
        if(ptr[0] == MAT_OPEN)
        {
            ptr++;
        }
        if(!IsRegAccess(ptr))
        {
            return false;
        }
    }while((ptr = String_Split(NULL, MAT_CLOSE)));
    
    return true;
}

/* return number of operands used*/
int GetParamValue(char* param,OperandByte op[],size_t len, Programme* prog)
{
    if(!op || len == 0 || !param || !prog)
    {
        return false;
    }
}

EAddressingType GetOperandType(char* param, List symbols)
{
    if(!param)
    {
        return eInvalid;
    }

    if(IsImmediate(param))
    {
        return eImmediate;
    }
    else if(IsMatAccess(param,symbols))
    {
        return eMetAccess;   
    }
    else if(IsRegAccess(param))
    {
        return eDirectRegister;
    }
    else if(IsLabel(param, symbols))
    {
        return eDirect;   
    }

    return eInvalid;
}


int GetCommandCode(char* command)
{
    int i=0;
    for(i=0; i< COMMAND_NUM_OF_ELEM; i++)
    {
        if(String_Compare(commandHandlers[i].command,command,String_Len(commandHandlers[i].command)) == 0)
        {
            return i;
        }
    }
    return -1;
}

size_t Handle_NoOperandCommand(char* command, char* params,void* context)
{
    return 1;
}

size_t Handle_SingleOperandCommands(char* command,char* params,void* context)
{
    return 1;
}

size_t Handle_TwoOperandCommands(char* command, char* params, void* context)
{
    /*for now*/
    if(!context)
    {
        return 1;
    }
    Programme* prog = context;
    char* param = String_Split(params,COMMA_STR);
    do
    {
        if(GetOperandType(param, prog->symbols) != eInvalid)
        {
            printf("%s\n",param);
        }
    }while((param = String_Split(NULL, COMMA_STR)));

    return 1;    
}






bool CommandHandler_IsLine(char* command)
{
    return Handler_HasHandler(command, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_Handle(char* command, char* params, Programme* prog)
{
    return Handler_Handle(command, params, prog, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_GetLineSize(char* command, char* params)
{
    return Handler_Handle(command, params, NULL, commandHandlers, COMMAND_NUM_OF_ELEM);
}



