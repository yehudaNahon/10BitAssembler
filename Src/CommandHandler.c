#include "Convert.h"
#include "CommandHandler.h"
#include "CommandHandlerInternals.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>
#include "Memory.h"
#include "CommandTypeHandlers.h"
#include "GeneralMacros.h"


#define GetHandlers() Handler handlers[] = {NoOperandHandler,SingleOperandHandler,TwoOperandsHandler}

Handler CommandHandler = {
    &CommandHandler_IsCommand,
    &CommandHandler_GetSize,
    &CommandHandler_Add,
};



bool CommandHandler_Add(const char* command,List* byte,List* symbols)
{
    GetHandlers();
    
    Handler* ptr = Handler_GetHandler(command,handlers,NUM_OF_ELEM(handlers));
    
    return ptr && ptr->Add(command,byte,symbols);
}

size_t CommandHandler_GetSize(const char* command)
{
    GetHandlers();
 
    Handler* ptr = Handler_GetHandler(command,handlers,NUM_OF_ELEM(handlers));
    
    if(!ptr)
    {
        return 0;
    }

    return ptr->GetSize(command);
}

bool CommandHandler_IsCommand(const char* command)
{
    GetHandlers();

    return Handler_HasHandler(command,handlers,NUM_OF_ELEM(handlers));
}

