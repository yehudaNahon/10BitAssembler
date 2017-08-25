#include "Convert.h"

#include <stdlib.h>


int Convert_StrToDecimal(const char* str)
{
    return strtol(str,NULL,10);
}


