#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "Node.h"

typedef struct Queue
{
    size_t count;
    Node* head;
    Node* tail;
}Queue;

Queue Queue_Init();

bool Queue_enqueue(Queue* queue, void* data);

void* Queue_dequeue(Queue* queue);

bool Queue_Empty(Queue* queue);

void* Queue_Peek(Queue* queue);

#endif