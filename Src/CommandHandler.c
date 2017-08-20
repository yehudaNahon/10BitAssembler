
#include "CommandHandler.h"

size_t Handle(char*,void*);

#define COMMAND_NUM_OF_ELEM (16)
Handler commandHandlers[] = {
    {"mov",&Handle},
    {"cmp",&Handle},
    {"add",&Handle},
    {"sub",&Handle},
    {"not",&Handle},
    {"clr",&Handle},
    {"lea",&Handle},
    {"inc",&Handle},
    {"dec",&Handle},
    {"jmp",&Handle},
    {"bne",&Handle},
    {"red",&Handle},
    {"prn",&Handle},
    {"jsr",&Handle},
    {"rts",&Handle},
    {"stop",&Handle}
};

size_t Handle(char* command, void* context)
{
    return 1;
}


bool CommandHandler_IsLine(char* command)
{
    return Handler_IsInList(command, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_AddLine(char* command, char* params, ByteTable* table)
{
    return Handler_AddLine(command, params, table, commandHandlers, COMMAND_NUM_OF_ELEM);
}





