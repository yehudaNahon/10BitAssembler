#include "Convert.h"
#include "CommandHandler.h"
#include "CommandHandlerInternals.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>

size_t Handle_NoOperandCommand(char* command, char* params,void* context);
size_t Handle_SingleOperandCommands(char* command,char* params,void* context);
size_t Handle_TwoOperandCommands(char* command, char* params, void* context);


size_t Handle_NoOperandsSize(char* command, char* params,void* context);
size_t Handle_SingleOperandsSize(char* command,char* params,void* context);
size_t Handle_TwoOperandsSize(char* command, char* params, void* context);

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

void PrintCommandByteIter(const void* data, size_t len, void* context)
{
    const CommandByte* byte = data;
    printf(" opcode:%d\n dest:%d\n src:%d\n type:%d\n",byte->opcode,byte->destOperand,byte->srcOperand,byte->type);
    printf("byte\n");
}


bool BuildCommandByte(char* commandStr,int destOperand, int srcOperand,CommandByte* byte)
{
    byte->opcode = GetCommandCode(commandStr);
    byte->destOperand = destOperand;
    byte->srcOperand = srcOperand;
    byte->type = eAbsolute;

    return true;
}


size_t Handle_NoOperandCommand(char* commandStr, char* params,void* context)
{
    CommandByte commandByte;
    Programme* prog = context;
    
    /* if a programme is provided to use*/
    if(prog)
    {
        if(BuildCommandByte(commandStr,OPERAND_DEFAULT,OPERAND_DEFAULT,&commandByte))
        {
            return 0;
        }
        if(!List_Add(&prog->code.bytes, &commandByte, sizeof(CommandByte)))
        {
            Log(eError, "Failed Adding command %s %s to the memory table",commandStr,params);
            return 0;
        }
    }

    return 1;
}

size_t Handle_SingleOperandCommands(char* commandStr,char* param,void* context)
{
    CommandByte commandByte;
    OperandByte operandByte;
    Programme* prog = context;
    
    size_t totalSize = 1;
    size_t size = 0;
    if((size = GetOperandSize(param) == 0))
    {
        return 0;
    }
    totalSize += size;

    /* if the user provided a programme add the data to it*/
    if(prog)
    {
        if(!BuildCommandByte(commandStr,OPERAND_DEFAULT,OPERAND_DEFAULT, &commandByte))
        {
            return 0;
        }

        if(!BuildOperandByte(param, prog, &operandByte))
        {
            return 0;
        }
        
        if(!List_Add(&prog->code.bytes, &commandByte, sizeof(CommandByte)) || !List_Add(&prog->code.bytes, &operandByte, sizeof(OperandByte)))
        {
            Log(eError, "Failed Adding command %s %s to the memory table",commandStr,param);
        }
    }

    return totalSize;
}

size_t Handle_TwoOperandCommands(char* commandStr, char* params, void* context)
{
    char buffer[MAX_LINE_LEN];
    CommandByte commandByte;
    OperandByte firstOperandByte,
                secondOperandByte;
    Programme* prog = context;
    char    *firstParam = buffer,
            *secondParam = NULL;
    size_t  retSize = 0,
            totalSize = 1;

    if(!commandStr || !params)
    {
        return 0;
    }

    String_Copy(buffer,params,MAX_LINE_LEN);

    secondParam = String_SplitToTwo(firstParam, COMMA_CH);
    if(!secondParam)
    {
        Log(eError,"recieved a single parameter in a 2 parameter command : %s %s",commandStr,params);
        return 0;
    }

    retSize = GetOperandSize(firstParam);
    if(!retSize)
    {
        return 0;
    }
    totalSize += retSize;

    retSize = GetOperandSize(secondParam);
    if(!retSize)
    {
        return 0;
    }
    totalSize += retSize;

    if(prog)
    {
        if(!BuildCommandByte(commandStr,OPERAND_DEFAULT,OPERAND_DEFAULT,&commandByte))
        {
            return 0;
        }
        if(!BuildOperandByte(firstParam,prog,&firstOperandByte))
        {
            return 0;
        }
        if(!BuildOperandByte(secondParam,prog,&secondOperandByte))
        {
            return 0;
        }
        if( !List_Add(&prog->code.bytes, &commandByte, sizeof(CommandByte)) || 
            !List_Add(&prog->code.bytes, &firstOperandByte, sizeof(OperandByte)) ||
            !List_Add(&prog->code.bytes, &secondOperandByte, sizeof(OperandByte)))
        {
            Log(eError, "Failed Adding command %s %s to the memory table",commandStr,params);
        }
        
    }

    return totalSize;    
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



