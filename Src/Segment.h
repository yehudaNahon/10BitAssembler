#ifndef DATA_TYPE_H
#define DATA_TYPE_H 

#include "SymbolTable.h"
#include "ByteTable.h"
#include "List.h"

typedef struct Segment
{
    List bytes;
    size_t counter;
}Segment;

Segment Segment_Init();

void Segment_Delete(Segment* seg);



#endif