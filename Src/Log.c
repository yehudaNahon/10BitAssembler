#include "Log.h"
#include <stdio.h>
#include "GeneralMacros.h"

#define MAX_STR (100)
typedef struct TypeConfig
{
    char str[MAX_STR];
    /*TODO : add colors support*/
}TypeConfig;

TypeConfig TypeLookUpTable[] = {
    {"Warning"},
    {"Error"},
    {"Info"}
};

TypeConfig DefualtType = {"UnKnown"};

void Log(ELogType type,const char* message)
{
    TypeConfig *config;

    if((int)type < NUM_OF_ELEM(TypeLookUpTable))
    {
        config = &TypeLookUpTable[(int)type];
    }
    else
    {
        config = &DefualtType;
    }

    printf("%s :: %s\n", config->str, message);
}