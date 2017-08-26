#include <stdio.h>
#include "CommandUtils.h"
#include "Memory.h"
#include "GeneralMacros.h"
#include "String.h"
#include "Operand.h"
#include "Log.h" 

bool CommandUtils_GetCommand(const char* line,char* buffer, size_t len)
{
    if(!line || !buffer || len == 0)
    {
        return false;
    }

    Memory_Copy(buffer,line,MIN(len,String_Len(line)));

    if(String_SplitToTwo(buffer,SPACE_CH) == NULL)
    {
        return false;
    }

    return true;
}

bool CommandUtils_GetOperands(const char* line,char* buffer, size_t len)
{
    char* index;

    if(!line || !buffer || len == 0)
    {
        return false;
    }

    index = String_FindChar(line,SPACE_CH);
    if(!index)
    {
        return false;
    }

    if(!Memory_Copy(buffer,index + 1,MIN(len,String_Len(line))))
    {
        return false;
    }

    return true;
}

char* CommandUtils_SplitOperands(char* operands,size_t len)
{
    return String_SplitToTwo(operands, COMMA_CH);
}

int CommandUtils_GetOpcode(const char* command,const CommandOpcodes opcodeList[],size_t len)
{
    size_t i=0;
    
    for(i=0; i < len; i++)
    {
        if(String_Compare(command,opcodeList[i].commandStr,String_Len(opcodeList[i].commandStr)) == 0)
        {
            return opcodeList[i].opcode;
        }
    }

    return -1;
}

bool CommandUtils_AddCommandByte(const char* command,const char* operands,const CommandOpcodes* opcodes, size_t len,List* bytes)
{
    char buffer[MAX_LINE_LEN];
    char* src = buffer;
    char* dst;
    int opcode = 0;
    EOperandType srcType = 0;
    EOperandType dstType = 0;
    
    opcode = CommandUtils_GetOpcode(command,opcodes,len);
    if(opcode == -1)
    {
        Log(eError, "Recieved wrong command : %s",command);
        return false;
    }
    
    if(operands)
    {
        String_Copy(buffer,operands,sizeof(buffer));
    
        dst = Operand_SplitOperands(buffer);
    
        if(src)
        {
            srcType = Operand_GetType(src);
            if(srcType == eInvalid)
            {
                Log(eError,"recived a wrong source operand : %s",src);
                return false;
            }
        }
    
        if(dst)
        {
            dstType = Operand_GetType(dst);
            if(dstType == eInvalid)
            {
                Log(eError,"recived a wrong destination operand : %s",dst);
                return false;
            }
        }
    }
    printf("opcode : %d src : %d dst : %d\n",opcode,srcType,dstType);
    Byte byte = CommandByte_Init(opcode, srcType,dstType);
    if(!Byte_Add(byte,bytes))
    {
        Log(eError, "Failed adding element to list : %s",command);
        return false;
    }
    
    return true;
}


bool CommandUtils_IsHandler(const char* command,const CommandOpcodes opcodeList[],size_t len)
{
    return CommandUtils_GetOpcode(command, opcodeList, len) != -1;
}
