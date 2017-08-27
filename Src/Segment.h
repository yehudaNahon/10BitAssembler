#ifndef DATA_TYPE_H
#define DATA_TYPE_H 

#include "List.h"

/*
    a segment in the code
    holdes a list of bytes and a counter of the size
*/
typedef struct Segment
{
    List bytes;
    size_t counter;
}Segment;

/*
    initialize a new segment
*/
Segment Segment_Init();

/*
    deletes a segment
*/
void Segment_Delete(Segment* seg);



#endif