#include "GeneralMacros.h"
#include "OperandHandler.h"
#include "OperandHandlerInternals.h"
#include "MatOperandHandler.h"
#include "RegOperandHandler.h"
#include "LabelOperandHandler.h"
#include "ImmediateOperandHandler.h"


#define GetHandlers() Handler handlers[] = {MatOperandHandler,RegOperandHandler,LabelOperandHandler,ImmediateOperandHandler}

Handler OperandHandler = {
    &OperandHandler_IsHandler,    
    &OperandHandler_GetSize,
    &OperandHandler_Add,
};


bool OperandHandler_IsHandler(const char* commandStr)
{
    GetHandlers();
    return Handler_HasHandler(commandStr,handlers,NUM_OF_ELEM(handlers));
}


size_t OperandHandler_GetSize(const char* commandStr)
{
    GetHandlers();
    Handler *ptr = Handler_GetHandler(commandStr,handlers,NUM_OF_ELEM(handlers));

    if(!ptr)
    {
        return 0;
    }
    return ptr->GetSize(commandStr);
}


bool OperandHandler_Add(const char* commandStr, List* bytes, List symbols)
{
    GetHandlers();
    Handler *ptr = Handler_GetHandler(commandStr,handlers,NUM_OF_ELEM(handlers));

    return ptr && ptr->Add(commandStr,bytes,symbols);
}


