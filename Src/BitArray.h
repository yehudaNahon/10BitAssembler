#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>
#include <stddef.h>
#include "List.h"

typedef struct BitArray
{
    size_t count;
    uint8_t array[];
}BitArray;

void PrintBits(uint8_t bytes[],size_t len);

void PrintBitsIter(const void* data,size_t len,void* context);


#endif