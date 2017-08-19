
#include "Handlers.h"

Handler commandHandlers[] = {
    {"mov",&Handler_MOV},
    {"cmp",&Handler_CMP},
    {"add",&Handler_ADD},
    {"sub",&Handler_SUB},
    {"not",&Handler_NOT},
    {"clr",&Handler_CLR},
    {"lea",&Handler_LEA},
    {"inc",&Handler_INC},
    {"dec",&Handler_DEC},
    {"jmp",&Handler_JMP},
    {"bne",&Handler_BNE},
    {"red",&Handler_RED},
    {"prn",&Handler_PRN},
    {"jsr",&Handler_JSR},
    {"rts",&Handler_RTS},
    {"stop",&Handler_STOP}
};

Handler dataHandlers[] = {
    {".data", &DataHandlers_Data},
    {".mat", &DataHandlers_Mat},
    {".string", &DataHandlers_String}
};


size_t DataHandlers_Data(char* params, void* context)
{
    return 1;
}

size_t DataHandlers_Mat(char* params, void* context)
{
    return 1;
}

size_t DataHandlers_String(char* params, void* context)
{
    return 1;
}

size_t Handler_MOV(char* params,void* context)
{
    return 1;
}

size_t Handler_CMP(char* params,void* context)
{
    return 1;
}

size_t Handler_ADD(char* params,void* context)
{
    return 1;
}

size_t Handler_SUB(char* params,void* context)
{
    return 1;
}

size_t Handler_NOT(char* params,void* context)
{
    return 1;
}

size_t Handler_CLR(char* params,void* context)
{
    return 1;
}

size_t Handler_LEA(char* params,void* context)
{
    return 1;
}

size_t Handler_INC(char* params,void* context)
{
    return 1;
}

size_t Handler_DEC(char* params,void* context)
{
    return 1;
}

size_t Handler_JMP(char* params,void* context)
{
    return 1;
}

size_t Handler_BNE(char* params,void* context)
{
    return 1;
}

size_t Handler_RED(char* params,void* context)
{
    return 1;
}

size_t Handler_PRN(char* params,void* context)
{
    return 1;
}

size_t Handler_JSR(char* params,void* context)
{
    return 1;
}

size_t Handler_RTS(char* params,void* context)
{
    return 1;
}

size_t Handler_STOP(char* params,void* context)
{
    return 1;
}



