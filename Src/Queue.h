#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#include "LinkedList.h"

/*
    A queue data structure
    
    in the back uses the linked list to manage elements
*/
typedef struct Queue
{
    LinkedList head;
}Queue;

/*
    initialize a new queue
*/
Queue Queue_Init();

/*
    add data to the end of the queue
*/
bool Queue_enqueue(Queue* queue,const void* data, size_t len);

/*
    remove one element from the front of the queue 
*/
size_t Queue_dequeue(Queue* queue, void* o_data);

/*
    returns wether or not the queue is empty
*/
bool Queue_Empty(Queue queue);

/*
    returns the next element to be removed without removing is
*/
size_t Queue_Peek(Queue queue,void* o_data);

/*
    iterate over the queue
*/
void Queue_ForEach(Queue queue,Iterator iter,void* context);

/*
    deletes all the queue elements
*/
void Queue_Delete(Queue* queue,Cleaner cleaner,void* context);

#endif