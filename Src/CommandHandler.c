#include "Convert.h"
#include "CommandHandler.h"
#include "CommandHandlerInternals.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>



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

size_t Handle_mov(char* params, void* context)
{
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

size_t Handle_cmp(char* params, void* context)
{
    return 1;        
}

size_t Handle_add(char* params, void* context)
{
    return 1;
}

size_t Handle_sub(char* params, void* context)
{
    return 1;
}

size_t Handle_not(char* params, void* context)
{
    return 1;
}

size_t Handle_clr(char* params, void* context)
{
    return 1;
}

size_t Handle_lea(char* params, void* context)
{
    return 1;
}

size_t Handle_inc(char* params, void* context)
{
    return 1;
}

size_t Handle_dec(char* params, void* context)
{
    return 1;
}

size_t Handle_jmp(char* params, void* context)
{
    return 1;
}

size_t Handle_bne(char* params, void* context)
{
    return 1;
}

size_t Handle_red(char* params, void* context)
{
    return 1;
}

size_t Handle_prn(char* params, void* context)
{
    return 1;
}

size_t Handle_jsr(char* params, void* context)
{
    return 1;
}

size_t Handle_rts(char* params, void* context)
{
    return 1;
}

size_t Handle_stop(char* params, void* context)
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
    return Handler_HasHandler(command, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_Handle(char* command, char* params, Programme* prog)
{
    return Handler_Handle(command, params, prog, commandHandlers, COMMAND_NUM_OF_ELEM);
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



