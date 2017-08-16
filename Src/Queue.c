#include "Queue.h"
#include "Memory.h"
#include "Log.h"

Queue Queue_Init()
{
    Queue new;
    new.count = 0;
    new.head = NULL;
    new.tail = NULL;

    return new;
}

bool Queue_enqueue(Queue* queue, void* data)
{
    /* allocate memory for the new LinkedList*/
    LinkedList* ptr = Memory_Allocate(sizeof(LinkedList));
    if(!ptr)
    {
        Log(eError, MEMORY_ERR);
        return false;
    }

    /* initialize new LinkedList*/
    LinkedList_Init(ptr,data);

    /* update fields */
    queue->tail = ptr;
    if(!queue->head)
    {
        queue->head = ptr;
    }

    queue->count++;

    return true;
}

void* Queue_dequeue(Queue* queue)
{
    LinkedList* ptr = NULL;
    void* data = NULL;

    /* validaty check*/
    if(queue->count == 0 || !queue->head)
    {
        return NULL;
    }

    /*change the queue and save the unpointer LinkedList*/
    ptr = queue->head;
    queue->head = ptr->next;
    data = ptr->data;
    
    /* delete the LinkedList block*/
    Memory_Delete(ptr);

    return data;
}

bool Queue_Empty(Queue* queue)
{
    return queue->count == 0;
}

void* Queue_Peek(Queue* queue)
{
    return queue? ( queue->head? queue->head->data : NULL ) : NULL;
}

