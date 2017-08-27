#ifndef SEGMENT_LIST_H
#define SEGMENT_LIST_H

#include "LinkedList.h"


/*
    becuse of the simmelarity of the List operation with the linkedList operation 
    this class is mirrly just a typedef to incapsulate the back-end operation from the 
    concept of a list
*/
typedef LinkedList List;


List List_Init();

size_t List_Get(List list, size_t index,void* o_ptr);

bool List_Add(List* list,const void* element, size_t length);

size_t List_Len(List list);

size_t List_Remove(List* list,void* o_ptr, Finder finder,void* context);

size_t List_FindData(List list, void** o_ptr,Finder finder,void* context);

void List_ForEach(List list,Iterator iter, void* context);

void List_Delete(List* list ,Cleaner cleaner,void* context);

bool List_AddToList(List* first,List* second);




#endif