#include "GeneralMacros.h"
#include "OperandHandler.h"
#include "OperandHandlerInternals.h"
#include "MatOperandHandler.h"
#include "RegOperandHandler.h"
#include "LabelOperandHandler.h"
#include "ImmediateOperandHandler.h"
#include "String.h"
#include "Operand.h"

#define GetHandlers() Handler handlers[] = {MatOperandHandler,RegOperandHandler,LabelOperandHandler,ImmediateOperandHandler}

Handler OperandsHandler = {
    &OperandHandler_IsHandler,    
    &OperandHandler_GetSize,
    &OperandHandler_Add,
};


#define MAX_LINE_LEN (800)
bool OperandHandler_IsHandler(const char* commandStr)
{
    char buffer[MAX_LINE_LEN];
    char* first = buffer;
    char* second;
    String_Copy(buffer,commandStr,sizeof(buffer));

    second = String_SplitToTwo(first,COMMA_CH);

    return Operand_GetType(first) != eInvalid  && Operand_GetType(first) != eInvalid;
}


size_t OperandHandler_GetSize(const char* commandStr)
{
    char buffer[MAX_LINE_LEN];
    char* first = buffer;
    char* second;
    String_Copy(buffer,commandStr,sizeof(buffer));

    second = Operand_SplitOperands(first);

    return Operand_GetOperandsSize(Operand_GetType(first),Operand_GetType(second));
}


bool OperandHandler_Add(const char* commandStr, List* bytes, List symbols)
{
    char buffer[MAX_LINE_LEN];
    char* first = buffer;
    char* second;
    String_Copy(buffer,commandStr,sizeof(buffer));

    second = Operand_SplitOperands(first);

    return Operand_AddOperands(first,second,bytes,symbols);
}




