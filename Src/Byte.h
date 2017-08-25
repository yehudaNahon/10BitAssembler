#ifndef BYTE_H 
#define BYTE_H
#include <stdint.h>
#include <stddef.h>
#include "List.h"

/* General for all bytes in the assembly file*/
#define BYTE_LEN (10)


typedef enum EEncodingType
{
    eAbsolute,
    eExternal,
    eRelocatable
}EEncodingType;


typedef struct Byte
{
    int value :BYTE_LEN;
}Byte;

bool Byte_Add(int value,List* bytes);










#endif

