#include "String.h"
#include "LabelOperandHandler.h"
#include "LabelOperandHandlerInternals.h"
#include "Log.h"
#include "Symbol.h"
#include "Operand.h"
#include "CommandHandler.h"

Handler LabelOperandHandler = {
    &LabelOperandHandler_IsHandler,
    &LabelOperandHandler_GetSize,
    &LabelOperandHandler_Add,
};


size_t LabelOperandHandler_GetSize(const char* param)
{
    return 1;
}


bool LabelOperandHandler_IsHandler(const char* param)
{
    const char* ligalChars = LETTERS_CH NUMBERS_CH UPPER_CASE_CH;
    if( CommandHandler.IsHandler(param) || String_Len(param) > MAX_LABEL_LEN || !String_IsLetter(param[0]) || !String_OnlyWithChars(param,ligalChars))
    {
        return false;
    }
    
    return true;
}

bool LabelOperandHandler_Add(const char* operand,List* bytes,List symbols)
{
    OperandByte byte;
    Symbol* ptr = NULL;    
    
    if(!operand || !bytes || !LabelOperandHandler_IsHandler(operand))
    {
        Log(eError, "Reiceived a none label operand : %s",operand);
        return false;
    }
    if(List_FindData(symbols,(void**)&ptr,&Symbol_Finder,operand) == 0)
    {
        return false;
    }
    
    if(!ptr)
    {    
        return false;
    }
    
    byte = OperandByte_Init(eLabel,ptr->address);
    return List_Add(bytes,&byte,sizeof(OperandByte));
}








