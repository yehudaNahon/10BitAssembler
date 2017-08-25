#include <stdio.h>
#include "DataHandler.h"
#include "DataCommandHandlers.h"
#include "DataHandlerInternals.h"
#include "Log.h"
#include "String.h"
#include "Memory.h"
#include "Convert.h"
#include "Assembly.h"
#include "GeneralMacros.h"

#define GetHandlers() Handler handlers[] = {DataCommandHandler,StringCommandHandler,MatCommandHandler}

Handler DataHandler = {
    &DataHandler_IsHandler,    
    &DataHandler_GetSize,
    &DataHandler_Add   
};


bool DataHandler_IsHandler(const char* data)
{
    GetHandlers();

    return Handler_HasHandler(data, handlers, NUM_OF_ELEM(handlers));
}

size_t DataHandler_GetSize(const char* data)
{
    GetHandlers();
 
    Handler* ptr = Handler_GetHandler(data,handlers,NUM_OF_ELEM(handlers));
    if(!ptr)
    {
        return 0;
    }

    return ptr->GetSize(data);
}

bool DataHandler_Add(const char* data, List* bytes,List symbols)
{
    GetHandlers();
 
    Handler* ptr = Handler_GetHandler(data, handlers,NUM_OF_ELEM(handlers));
    
    return ptr && ptr->Add(data,bytes,symbols);
}
