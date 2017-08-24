#include "Operand.h"
#include "CommandHandler.h"
#include "Convert.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>

#define DIRECT_CH ('#')
bool IsImmediate(char* param)
{
    return param[0] == DIRECT_CH;
}

bool GetImmediate(char* param,int* o_val)
{
    *o_val =  Convert_StrToDecimal(&param[1]);
    return true;
}

bool IsLabel(char* param)
{
    /* for now will only check that its not a label*/
    if(CommandHandler_IsLine(param))
    {
        return false;
    }

    return true;
}

bool GetLabel(char* param,int* o_val,List symbols)
{
    Symbol* ptr = NULL;    
    
    if(List_FindData(symbols,(void**)&ptr,&Symbol_Finder,param) == 0)
    {
        return false;
    }
 
    if(ptr)
    {
        *o_val = ptr->address;
    }
 
    return true;
}


#define REG_CH ('r')
bool IsRegAccess(char* param)
{
    return param[0] == REG_CH && Convert_StrToDecimal(&param[1]) < NUM_OF_REGS;
}

bool GetRegAccess(char* param,int* o_val)
{
    *o_val = Convert_StrToDecimal(&param[1]);
    return true;
}


bool IsMatAccess(char* param)
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
    if(!IsLabel(buffer))
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

bool GetMatAccess(char* param, int* o_val, List symbols)
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
    if(!IsLabel(buffer))
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


EOperandType GetOperandType(char* param)
{
    if(!param)
    {
        return eInvalid;
    }

    if(IsImmediate(param))
    {
        return eImmediate;
    }
    else if(IsMatAccess(param))
    {
        return eMetAccess;   
    }
    else if(IsRegAccess(param))
    {
        return eDirectRegister;
    }
    else if(IsLabel(param))
    {
        return eDirect;   
    }

    return eInvalid;
}

size_t GetOperandSize(char* operandStr)
{
    switch(GetOperandType(operandStr))
    {
        
        case eImmediate:
        case eDirect:
        case eMetAccess:
        case eDirectRegister:
            return 1;
        case eInvalid : 
            return 0;
        default:
            Log(eError, "recieved a unsported operandType");
            return 0;
    }
}

bool GetOperandValue(char* operand,EOperandType type, Programme* prog,int* o_value)
{
    switch(type)
    {
        case eImmediate:
            return GetImmediate(operand,o_value);
        case eDirect:
            return GetLabel(operand,o_value,prog->symbols);
        case eMetAccess:
            return GetMatAccess(operand,o_value,prog->symbols); 
        case eDirectRegister:
            return GetRegAccess(operand,o_value);
        case eInvalid : 
            break;
        default:
            Log(eError, "recieved a unsported operandType");
    }
    return false;
}

bool BuildOperandByte(char* operand,Programme* prog,OperandByte* byte)
{
    int value = 0;
    EOperandType type = GetOperandType(operand);
    if(type == eInvalid)
    {
        return false;
    }
    
    byte->type = type;
    printf("operand:%s \n type:%d\n",operand,type);
    if(!GetOperandValue(operand,type, prog,&value))
    {
        printf("failed\n");
        return false;
    }
    printf(" value:%d\n",value);
    byte->value = value;
    
    return true;
}
