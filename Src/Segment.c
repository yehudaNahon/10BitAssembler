
#include "Segment.h"

Segment Segment_Init()
{
    Segment type;
    type.bytes = List_Init();
    type.counter = 0;

    return type;
}













