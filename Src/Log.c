#include <stdio.h>
#include "Log.h"

const char* LookUpTable[] = {
    "Warning",
    "Error",
    "Info"
};

void Log(ELogType type, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("%s :: ",LookUpTable[type]);
    vfprintf(stdout, fmt, args);
    printf("\n");
    va_end(args);
}
