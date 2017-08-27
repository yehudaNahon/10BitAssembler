#ifndef BYTE_H 
#define BYTE_H

#include <stdint.h>
#include <stddef.h>
#include "List.h"

/* General for all bytes in the assembly file*/
#define BYTE_LEN (10)

/* 
    a enum of the addressing types (the enum value is the addressing value)
*/
typedef enum EEncodingType
{
    eAbsolute,
    eExternal,
    eRelocatable
}EEncodingType;

/* a general programmes byte*/
typedef struct Byte
{
    int value :BYTE_LEN;
}Byte;

/* 
    initialize the byte
*/
Byte Byte_Init(int value);

/*
    adds the byte to the byte list
*/
bool Byte_Add(Byte byte,List* bytes);










#endif

