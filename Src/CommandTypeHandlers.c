#include "CommandTypeHandlers.h"
#include "CommandTypeHandlersInternals.h"
#include "Operand.h"
#include "OperandHandler.h"
#include "CommandByte.h"
#include "CommandUtils.h"
#include "Memory.h"
#include "String.h"
#include "GeneralMacros.h"
#include "Log.h"
#include <stdio.h>



Handler NoOperandHandler = {
    &NoOperandHandler_IsHandler,
    &NoOperandHandler_GetSize,
    &NoOperandHandler_Add
};


Handler SingleOperandHandler = {
    &SingleOperandHandler_IsHandler,
    &SingleOperandHandler_GetSize,
    &SingleOperandHandler_Add
};


Handler TwoOperandsHandler = {
    &TwoOperandsHandler_IsHandler,
    &TwoOperandsHandler_GetSize,
    &TwoOperandsHandler_Add
};



const CommandOpcodes NoOperand_Opcodes[] = {
    {"rts",14},
    {"stop",15},
}; 

bool NoOperandHandler_Add(const char* commandStr,List* bytes,List symbols)
{
    if(!commandStr || !bytes)
    {
        Log(eError, "TwoOperandsHandler_Add :: recieved a null pointer");
        return false;
    }

    if(!CommandUtils_AddCommandByte(commandStr,NULL,NoOperand_Opcodes,NUM_OF_ELEM(NoOperand_Opcodes),bytes))
    {
        Log(eError, "Failed Adding command to the memory table : %s",commandStr);
        return false;
    }

    return true;
}


size_t NoOperandHandler_GetSize(const char* commandStr)
{
    return 1;
}


bool NoOperandHandler_IsHandler(const char* commandStr)
{
    /*printf("in is handlers : %s\n",commandStr);*/
    return CommandUtils_IsHandler(commandStr,NoOperand_Opcodes,NUM_OF_ELEM(NoOperand_Opcodes));
}

const CommandOpcodes SingleOperand_Opcodes[] = {
    {"not",4},
    {"clr",5},
    {"inc",7},
    {"dec",8},
    {"jmp",9},
    {"bne",10},
    {"red",11},
    {"prn",12},
    {"jsr",13},
};

bool SingleOperandHandler_Add(const char* commandStr,List* bytes,List symbols)
{
    char operand[MAX_OPERAND_STR_LEN];
    
    if(!commandStr || !bytes)
    {
        Log(eError, "TwoOperandsHandler_Add :: recieved a null pointer");
        return false;
    }

    if(!CommandUtils_GetOperands(commandStr,operand,MAX_OPERAND_STR_LEN))
    {
        Log(eError,"did not recieved any operands : %s", commandStr);
        return 0;
    }
    
    if(!CommandUtils_AddCommandByte(commandStr,operand,SingleOperand_Opcodes,NUM_OF_ELEM(SingleOperand_Opcodes),bytes))
    {
        Log(eError, "Failed Adding command to the memory table : %s",commandStr);
        return false;
    }

    if(!OperandsHandler.Add(operand,bytes,symbols))
    {
        Log(eError, "Failed Adding operand to list");
        return false;
    }

    return true;
}


size_t SingleOperandHandler_GetSize(const char* commandStr)
{
    char operand[MAX_OPERAND_STR_LEN];

    CommandUtils_GetOperands(commandStr,operand,MAX_OPERAND_STR_LEN);

    return OperandsHandler.GetSize(operand) + 1;
}


bool SingleOperandHandler_IsHandler(const char* commandStr)
{
    return CommandUtils_IsHandler(commandStr,SingleOperand_Opcodes,NUM_OF_ELEM(SingleOperand_Opcodes));
}



const CommandOpcodes TwoOperands_Opcodes[] = {
    {"mov",0},
    {"cmp",1},
    {"add",2},
    {"sub",3},
    {"lea",6}
};


bool TwoOperandsHandler_Add(const char* commandStr,List* bytes,List symbols)
{
    char operands[MAX_OPERAND_STR_LEN];
    
    if(!commandStr || !bytes)
    {
        Log(eError, "TwoOperandsHandler_Add :: recieved a null pointer");
        return false;
    }
    
    if(!CommandUtils_GetOperands(commandStr,operands,MAX_OPERAND_STR_LEN))
    {
        Log(eError,"did not recieved any operands : %s", commandStr);
        return 0;
    }

    if(!CommandUtils_AddCommandByte(commandStr,operands,TwoOperands_Opcodes,NUM_OF_ELEM(TwoOperands_Opcodes),bytes))
    {
        Log(eError, "Failed Adding command to the memory table : %s",commandStr);
        return false;
    }
    

    if(!OperandsHandler.Add(operands,bytes,symbols))
    {
        Log(eError, "Failed Adding operand to list : %s",operands);
        return false;
    }


    return true;
}


size_t TwoOperandsHandler_GetSize(const char* commandStr)
{
    size_t size = 1;
    char operand[MAX_OPERAND_STR_LEN];
    char* secondOperand = NULL;

    if(!CommandUtils_GetOperands(commandStr,operand,MAX_OPERAND_STR_LEN))
    {
        Log(eError,"did not recieved any operands : %s", commandStr);
        return 0;
    }
    
    secondOperand = CommandUtils_SplitOperands(operand,MAX_OPERAND_STR_LEN);
    if(!secondOperand)
    {
        Log(eError, "Recieved only 1 operand in a 2 operand command : %s", commandStr);
        return 0;
    }

    return OperandsHandler.GetSize(operand) + OperandsHandler.GetSize(secondOperand) + 1;

}


bool TwoOperandsHandler_IsHandler(const char* commandStr)
{
    return CommandUtils_IsHandler(commandStr,TwoOperands_Opcodes,NUM_OF_ELEM(TwoOperands_Opcodes));
}


