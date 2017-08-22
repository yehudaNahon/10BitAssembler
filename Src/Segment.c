
#include "Segment.h"

Segment Segment_Init()
{
    Segment type;
    type.bytes = List_Init();
    type.counter = 0;

    return type;
}

void Segment_Delete(Segment* seg)
{
    List_Delete(&seg->bytes,NULL,NULL);
}











