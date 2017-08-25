#include "Byte.h"
#include <stdio.h>

bool Byte_Add(int value,List* bytes)
{
    Byte byte;
    byte.value = value;
    return List_Add(bytes,&byte,sizeof(byte));
}


