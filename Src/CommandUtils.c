#include <stdio.h>
#include "CommandUtils.h"
#include "Memory.h"
#include "GeneralMacros.h"
#include "String.h"
#include "Operand.h"
#include "Log.h" 

/*
    write the command to buffer till end or till len bytes

    return  :   true - sucess
                false - falied
*/
bool CommandUtils_GetCommand(const char* line,char* buffer, size_t len)
{
    if(!line || !buffer || len == 0)
    {
        return false;
    }

    /*copies the line to the buffer*/
    Memory_Copy(buffer,line,MIN(len,String_Len(line)));

    /* split the buffer by the first space char*/
    if(String_SplitToTwo(buffer,SPACE_CH) == NULL)
    {
        return false;
    }

    return true;
}

/*
    writes operands to the buffer till end or till len bytes
*/
bool CommandUtils_GetOperands(const char* line,char* buffer, size_t len)
{
    char* index;

    if(!line || !buffer || len == 0)
    {
        return false;
    }

    /*finds the operand (write after the space char)*/
    index = String_FindChar(line,SPACE_CH);
    if(!index)
    {
        return false;
    }

    /*copy from the operand index till the max pussible length*/
    if(!Memory_Copy(buffer,index + 1,MIN(len,String_Len(line))))
    {
        return false;
    }

    return true;
}

/*
    places a NULL char between the operand to create to seperate strings
*/
char* CommandUtils_SplitOperands(char* operands,size_t len)
{
    return String_SplitToTwo(operands, COMMA_CH);
}

/*
    Returns the commands opcode

    command :   the command line (can have over chars but the command should start at index 0)
    commandOpcodes  :   a list of command opcodes by strings
    len : the length of the array

    return :    the command opcode on error -1
    */
int CommandUtils_GetOpcode(const char* command,const CommandOpcodes opcodeList[],size_t len)
{
    size_t i=0;
    
    /*run on all the opcodes*/
    for(i=0; i < len; i++)
    {
        /*compare the command to the opcode command string*/
        if(String_Compare(command,opcodeList[i].commandStr,String_Len(opcodeList[i].commandStr)) == 0)
        {
            return opcodeList[i].opcode;
        }
    }

    return -1;
}

/*
    parses the command to a command byte and add it to the byte list
*/
bool CommandUtils_AddCommandByte(const char* command,const char* operands,const CommandOpcodes* opcodes, size_t len,List* bytes)
{
    char buffer[MAX_LINE_LEN];
    char* src = buffer;
    char* dst;
    int opcode = 0;
    EOperandType srcType = 0;
    EOperandType dstType = 0;
    
    /*return the opcode of the command*/
    opcode = CommandUtils_GetOpcode(command,opcodes,len);
    if(opcode == -1)
    {
        Log(eError, "Recieved wrong command : %s",command);
        return false;
    }
    
    /*if theres any operands*/
    if(operands)
    {
        /*copy the operand to the buffer*/
        String_Copy(buffer,operands,sizeof(buffer));
    
        /*spilt the operands*/
        dst = Operand_SplitOperands(buffer);
    
        /*if theres a src operand*/
        if(src)
        {
            srcType = Operand_GetType(src);
            if(srcType == eInvalid)
            {
                Log(eError,"recived a wrong source operand : %s",src);
                return false;
            }
        }
        
        /*if theres a destination operand*/
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
    
    /*create operand byte and add it to the list*/
    Byte byte = CommandByte_Init(opcode, dstType,srcType);
    if(!Byte_Add(byte,bytes))
    {
        Log(eError, "Failed adding element to list : %s",command);
        return false;
    }
    
    return true;
}

/*
    search in opcode list if one of the opcodes matches the command
*/
bool CommandUtils_IsHandler(const char* command,const CommandOpcodes opcodeList[],size_t len)
{
    return CommandUtils_GetOpcode(command, opcodeList, len) != -1;
}
