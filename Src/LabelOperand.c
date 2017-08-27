#include "String.h"
#include "LabelOperand.h"
#include "Log.h"
#include "Symbol.h"
#include "Operand.h"
#include "CommandHandler.h"
#include <stdio.h>
#include "BitArray.h"

#define MAX_LABEL_LEN (30)

int Label_GetValue(char* labelStr,List symbols)
{
    Byte byte;
    Symbol* ptr = NULL;    
    
    if(!labelStr)
    {
        Log(eError, "Reiceived a none label operand : %s",labelStr);
        return -1;
    }
    if(List_FindData(symbols,(void**)&ptr,&Symbol_Finder,labelStr) == 0)
    {
        return -1;
    }
    
    if(!ptr)
    {    
        return -1;
    }
    
    return ptr->address;
}


size_t SizeLabel()
{
    return 1;
}


bool IsLabel(const char* param)
{
    const char* ligalChars = LETTERS_CH NUMBERS_CH UPPER_CASE_CH;
    /* check it is not a command of is to big also that the chrs are all ligal chars for the name*/
    if( CommandHandler.IsHandler(param) || String_Len(param) > MAX_LABEL_LEN || !String_IsLetter(param[0]) || !String_OnlyWithChars(param,ligalChars))
    {
        return false;
    }
    
    return true;
}

bool AddLabel(char* operand,List* bytes,List* symbols)
{
    Byte byte;
    Symbol* ptr = NULL;    
    
    if(!operand || !bytes || !IsLabel(operand))
    {
        Log(eError, "Reiceived a none label operand : %s",operand);
        return false;
    }
    if(List_FindData(*symbols,(void**)&ptr,&Symbol_Finder,operand) == 0)
    {
        return false;
    }
    
    if(!ptr)
    {    
        return false;
    }

    byte = OperandByte_Init(ptr->dataType == eExternalSymbol ? eExternal : eRelocatable,ptr->address);
    return Byte_Add(byte,bytes);
}








