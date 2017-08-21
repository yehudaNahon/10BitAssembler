
#include "Segment.h"

Segment Segment_Init()
{
    Segment type;
    type.memory = ByteTable_Init();
    type.counter = 0;

    return type;
}













