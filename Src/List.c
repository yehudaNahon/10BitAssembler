
#include "List.h"





List List_Init()
{
    return LinkedList_Init();
}

size_t List_Get(List list, size_t index,void* o_ptr)
{
    return LinkedList_Get(list,index,o_ptr);
}

bool List_Add(List* list,const void* element, size_t length)
{
    return LinkedList_Add(list,element,length);
}

size_t List_Len(List list)
{
    return LinkedList_Len(list);
}

size_t List_Remove(List* list,void* o_ptr, Finder finder,void* context)
{
    return LinkedList_Remove(list,o_ptr,finder,context);
}

size_t List_FindData(List list, void** o_ptr,Finder finder,void* context)
{
    return LinkedList_FindData(list, o_ptr, finder, context);    
}

void List_ForEach(List list,Iterator iter, void* context)
{
    return LinkedList_ForEach(list, iter, context);
}

void List_Delete(List* list ,Cleaner cleaner,void* context)
{
    return LinkedList_Delete(list, cleaner, context);
}



