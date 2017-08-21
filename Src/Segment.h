#ifndef DATA_TYPE_H
#define DATA_TYPE_H 

#include "SymbolTable.h"
#include "ByteTable.h"


typedef struct Segment
{
    ByteTable memory;
    size_t counter;
}Segment;

Segment Segment_Init();





#endif