#include "Convert.h"
#include "CommandHandler.h"
#include "String.h"
#include "Log.h"
#include <stdio.h>
#include "Memory.h"
#include "CommandTypeHandlers.h"
#include "GeneralMacros.h"

/* an array of child handlers to use*/
#define GetHandlers() Handler handlers[] = {NoOperandHandler,SingleOperandHandler,TwoOperandsHandler}


/*
    add a new command line to the byte list

    command : the command line
    byte    : a list of bytes to add the command to
    symbols : the programmes symbol list

    return :    true - success
                false- failed
*/
bool CommandHandler_Add(const char* command,List* byte,List* symbols)
{
    GetHandlers();

    /*get a handler that can handle this command*/
    Handler* ptr = Handler_GetHandler(command,handlers,NUM_OF_ELEM(handlers));
    
    /* return the handlers response*/
    return ptr && ptr->Add(command,byte,symbols);
}

/*
    return the command size

    command : the command line

    return  : the length on programmes bytes of the command
*/
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

/*
    return wether or not the command can be handled with this handler

    command : the command line

    return  : true - i can handle this command
*/
bool CommandHandler_IsCommand(const char* command)
{
    GetHandlers();

    return Handler_HasHandler(command,handlers,NUM_OF_ELEM(handlers));
}


/* the handlers functions*/
Handler CommandHandler = {
    &CommandHandler_IsCommand,
    &CommandHandler_GetSize,
    &CommandHandler_Add,
};
