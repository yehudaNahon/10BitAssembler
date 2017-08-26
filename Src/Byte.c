#include "Byte.h"
#include <stdio.h>

bool Byte_Add(Byte byte,List* bytes)
{
    return List_Add(bytes,&byte,sizeof(byte));
}

Byte Byte_Init(int value)
{
    Byte byte;
    byte.value = value;
    return byte;
}
