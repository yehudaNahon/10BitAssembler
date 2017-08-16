#include "LinkedList.h"
#include "LinkedListInternals.h"


#include <stdio.h>
#include "Memory.h"
#include "Log.h"


LinkedList* LinkedList_Next(LinkedList* list)
{
    return list ? list->next : NULL;
}

LinkedList LinkedList_Init()
{
    LinkedList list;
    
    list.data = NULL;
    list.length = 0;
    list.next = NULL;
    
    return list;
}

size_t LinkedList_Get(LinkedList* list, size_t index, void* o_data)
{
    /* validaty check*/
    if(!list)
    {
        o_data = NULL;
        return 0;
    }

    /* stop condition*/
    if(index == 0)
    {
        /* in case its empty will be with null and length 0*/
        o_data = list->data;
        return list->length;
    }

    /* if theres no child return error*/
    if(!LinkedList_Next(list))
    {
        o_data = NULL;
        return 0;
    }

    /* send question to next LinkedList*/
    return LinkedList_Get(LinkedList_Next(list), index - 1, o_data);
}

bool LinkedList_Add(LinkedList* list, void* data, size_t length)
{
    LinkedList* ptr = NULL;
    
    if(!list || !data || length == 0)
    {
        return false;
    }

    /* if theres no son*/
    if(!LinkedList_Next(list))
    {
        /* if i have no data*/
        if(!list->data)
        {

            /* allocate memory*/
            list->data = Memory_Allocate(length);
            if(!data)
            {
                Log(eError, MEMORY_ERR);
                return false;
            }

            /* copy data */
            Memory_Copy(list->data,data,length);

            return true;
        }
        else
        {
            
            /* create new node*/
            ptr = Memory_Allocate(sizeof(LinkedList));
            if(!ptr)
            {
                Log(eError, MEMORY_ERR);
                return false;
            }

            /* allocate space for data*/
            ptr->data = Memory_Allocate(length);
            if(!ptr->data)
            {
                Log(eError,MEMORY_ERR);
                Memory_Delete(ptr);
                return false;
            }

            /* set new node with data*/
            Memory_Copy(list->data, data, length);
            ptr->length = length;
            ptr->next = NULL;
    
            list->next = ptr;

            return true;
        }
    }

    /* in case theres a child tell him to add the data*/
    return LinkedList_Add(LinkedList_Next(list), data, length);
}

size_t LinkedList_Length(LinkedList* list)
{
    /* validaty check*/
    if(!list || list->data == NULL)
    {
        return 0;
    }

    /* if theres data in me but i have no child*/
    if(!LinkedList_Next(list))
    {
        return 1;
    }

    /* return the length of my child + me*/
    return LinkedList_Length(LinkedList_Next(list)) + 1;
}

size_t LinkedList_FindData(LinkedList* list, void* o_data, Finder finder,void* context)
{
    /* validaty check */
    if(!list || !finder || !list->data || list->length == 0)
    {
        return 0;
    }

    /* check if the data in me is the correct data*/
    if(finder && finder(list->data, list->length,context))
    {
        o_data = list->data;
        return list->length;
    }

    /* return my child result*/
    return LinkedList_FindData(LinkedList_Next(list), o_data, finder,context);
}


size_t LinkedList_Remove(LinkedList* list,void* o_data, Finder finder,void* context)
{
    /* validaty check */
    if(!list || !finder || !list->data || list->length == 0)
    {
        return 0;
    }

    /* check if the data in me is the correct data*/
    if( finder && finder(list->data, list->length,context))
    {
        o_data = list->data;
        return list->length;
    }

    /* return my child result*/
    return LinkedList_FindData(LinkedList_Next(list), o_data, finder,context);
}

void LinkedList_ForEach(LinkedList* list,Iterator iter, void* context)
{
    /* validaty check*/
    if(!list)
    {
        return;
    }

    /*if theres data*/
    if(list->data && iter)
    {
        iter(list->data,&list->length,context);
    }
    
    /*if theres child*/
    if(LinkedList_Next(list))
    {
        LinkedList_ForEach(LinkedList_Next(list), iter, context);
    }
}


void LinkedList_Delete(LinkedList* list, Cleaner cleaner,void* context)
{
    /* validaty check*/
    if(!list)
    {
        return;
    }

    /* if i have data*/
    if(list->data)
    {
        /* if user provided free resources function*/
        if(cleaner)
        {
            cleaner(list->data);
        }

        Memory_Delete(list->data);
        list->data = NULL;
        list->length = 0;
    }

    /* if i have a child*/
    if(LinkedList_Next(list))
    {
        /*tell the child to delete its data*/
        LinkedList_Delete(LinkedList_Next(list),cleaner,context);

        /* delete childs data*/
        Memory_Delete(LinkedList_Next(list));
        list->next = NULL;
    }
}

