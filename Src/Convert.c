#include "Convert.h"
#include <stdio.h>
#include <stdlib.h>


int Convert_StrToDecimal(const char* str)
{
    return strtol(str,NULL,10);
}


void Convert_SwapArray(char* array,size_t len)
{
    int i = 0;
    char temp;
    for(i = 0 ; i< len / 2 ; i++)
    {
        /* not using the += technic becuse of the possibilty of a over flow*/
        temp = array[i];
        array[i] = array[len-i - 1];
        array[len-i - 1] = temp;
    }
}

void Convert_DecimalToBase4Str(int num,char* buffer,size_t len)
{
    char baseDigits[] = {'a', 'b', 'c', 'd'};
    int i=0;

    if(num == 0)
    {
        buffer[0] = baseDigits[0];
    }

    /* convert to the indicated base */
    for(i = 0 ; num != 0 && i < len ; i++)
    {
        buffer[i] = baseDigits[num % 4];
        num = num / 4;
    }
    
    Convert_SwapArray(buffer,i);
}

