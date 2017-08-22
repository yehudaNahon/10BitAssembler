#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "LinkedList.h"

typedef struct Queue
{
    LinkedList head;
}Queue;

Queue Queue_Init();

bool Queue_enqueue(Queue* queue,const void* data, size_t len);

size_t Queue_dequeue(Queue* queue, void* o_data);

bool Queue_Empty(Queue queue);

size_t Queue_Peek(Queue queue,void* o_data);

void Queue_ForEach(Queue queue,Iterator iter,void* context);

void Queue_Delete(Queue* queue,Cleaner cleaner,void* context);

#endif