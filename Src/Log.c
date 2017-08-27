#include <stdio.h>
#include "Log.h"

#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

const char* LookUpTable[] = {
    KYEL"Warning",
    KRED"Error",
    KGRN"Info"
};

void Log(ELogType type, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("%s :: "KWHT,LookUpTable[type]);
    vfprintf(stdout, fmt, args);
    printf("\n");
    va_end(args);
}
