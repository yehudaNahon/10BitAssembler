
#include "Handlers.h"

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

#define DATA_NUM_OF_ELEM (3)
Handler dataHandlers[] = {
    {".data", &Handle},
    {".mat", &Handle},
    {".string", &Handle}
};

size_t Handle(char* line, void* context)
{
    return 1;
}


bool CommandHandler_IsCommandLine(char* line)
{
    return Handler_IsInList(line, commandHandlers, COMMAND_NUM_OF_ELEM);
}

size_t CommandHandler_AddCommandLine(char* line,LinkedList* list)
{
    return Handler_AddLine(line, list, commandHandlers, COMMAND_NUM_OF_ELEM);
}

bool DataHandler_IsDataLine(char* line)
{
    return Handler_IsInList(line, dataHandlers, DATA_NUM_OF_ELEM);
}

size_t DataHandler_AddDataLine(char* line,LinkedList* list)
{
    return Handler_AddLine(line, list, dataHandlers, DATA_NUM_OF_ELEM);
}





