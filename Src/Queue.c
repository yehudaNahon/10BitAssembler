#include "Queue.h"
#include "Memory.h"
#include "Log.h"

Queue Queue_Init()
{
    Queue new;
    new.head =  LinkedList_Init();

    return new;
}

bool Queue_enqueue(Queue* queue,const void* data, size_t len)
{
    return LinkedList_Add(&queue->head, data, len);
}

/*
    Will return true always and by that will get the first element
*/
bool GetFirst(void* data, size_t len, void* context)
{
    return true;
}

size_t Queue_dequeue(Queue* queue, void* o_data)
{
    return LinkedList_Remove(&queue->head, o_data,&GetFirst, NULL);
}

bool Queue_Empty(Queue queue)
{
    return LinkedList_Len(queue.head);
}

size_t Queue_Peek(Queue queue,void* o_data)
{
    return LinkedList_Get(queue.head,0,o_data);
}

void Queue_ForEach(Queue queue,Iterator iter,void* context)
{
    LinkedList_ForEach(queue.head,iter,context);
}