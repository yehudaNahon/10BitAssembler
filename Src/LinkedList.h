#ifndef LinkedList_H
#define LinkedList_H

#include <stddef.h>
#include <stdbool.h>
#include "Container.h"

typedef struct LinkedList
{
    size_t length;
    void* data;
    struct LinkedList* next;    
}LinkedList;


LinkedList LinkedList_Init();

size_t LinkedList_Get(LinkedList* list, size_t index,void* o_data);

bool LinkedList_Add(LinkedList* list, void* data, size_t length);

size_t LinkedList_Length(LinkedList* list);

size_t LinkedList_Remove(LinkedList* list,void* o_data, Finder finder,void* context);

size_t LinkedList_FindData(LinkedList* list, void* o_data,Finder finder,void* context);

void LinkedList_ForEach(LinkedList* list,Iterator iter, void* context);

void LinkedList_Delete(LinkedList* list ,Cleaner cleaner,void* context);



#endif