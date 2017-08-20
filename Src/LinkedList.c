#include "LinkedList.h"
#include "LinkedListInternals.h"


#include <stdio.h>
#include "Memory.h"
#include "Log.h"


LinkedList LinkedList_Init()
{
    LinkedList list;
    
    list.data = NULL;
    list.length = 0;
    list.next = NULL;
    
    return list;
}

size_t LinkedList_Get(LinkedList list, size_t index, void* o_data)
{
    /* stop condition*/
    if(index == 0)
    {
        /* in case its empty will be with null and length 0*/
        o_data = list.data;
        return list.length;
    }

    /* if theres no child return error*/
    if(!list.next)
    {
        o_data = NULL;
        return 0;
    }

    /* send question to next LinkedList*/
    return LinkedList_Get(*list.next, index - 1, o_data);
}

bool LinkedList_Add(LinkedList* list,const void* data, size_t length)
{
    LinkedList* ptr = NULL;
    
    if(!data || length == 0)
    {
        return false;
    }

    
    /* if theres no son*/
    if(!list->next)
    {
        /* if i have no data*/
        if(!list->data)
        {
            /* allocate memory*/
            list->data = Memory_Allocate(length);
            if(!list->data)
            {
                Log(eError, MEMORY_ERR);
                return false;
            }
            
            /* copy data */
            Memory_Copy(list->data,data,length);
            list->length = length;
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
            Memory_Copy(ptr->data, data, length);
            ptr->length = length;
            ptr->next = NULL;
    
            list->next = ptr;

            return true;
        }
    }

    /* in case theres a child tell him to add the data*/
    return LinkedList_Add(list->next, data, length);
}

size_t LinkedList_Len(LinkedList list)
{
    /* validaty check*/
    if(list.data == NULL)
    {
        return 0;
    }

    /* if theres data in me but i have no child*/
    if(!list.next)
    {
        return 1;
    }

    /* return the length of my child + me*/
    return LinkedList_Len(*list.next) + 1;
}

size_t LinkedList_FindData(LinkedList list, void* o_data, Finder finder,void* context)
{
    /* validaty check */
    if(!finder || !list.data || list.length == 0)
    {
        return 0;
    }

    /* check if the data in me is the correct data*/
    if(finder && finder(list.data, list.length,context))
    {
        o_data = list.data;
        return list.length;
    }

    /* return my child result*/
    return LinkedList_FindData(*list.next, o_data, finder,context);
}


size_t LinkedList_Remove(LinkedList* list,void* o_data, Finder finder,void* context)
{
    size_t len = 0;
    LinkedList* ptr = NULL;
    /* validaty check */
    if(!finder || !list->data || list->length == 0)
    {
        return 0;
    }

    /* check if the data in me is the correct data*/
    if( finder && finder(list->data, list->length,context))
    {
        /* save the elements data pointers*/
        o_data = list->data;
        len = list->length;
        
        /*copy the next nodes information*/
        if(list->next)
        {
            list->data = list->next->data;
            list->length = list->next->length;
            ptr = list->next;
            list->next = ptr->next;
        
            /*free the next node data*/
            Memory_Delete(ptr);
        }
        else
        {
            list->data = NULL;
            list->length = 0;
        }
        return len;
    }

    /* return my child result*/
    return LinkedList_Remove(list->next, o_data, finder,context);
}

void LinkedList_ForEach(LinkedList list,Iterator iter, void* context)
{
    /*if theres data*/
    if(list.data && iter)
    {
        iter(list.data,list.length,context);
    }
    
    /*if theres child*/
    if(list.next)
    {
        LinkedList_ForEach(*list.next, iter, context);
    }
}


void LinkedList_Delete(LinkedList* list, Cleaner cleaner,void* context)
{
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
    if(list->next)
    {
        /*tell the child to delete its data*/
        LinkedList_Delete(list->next,cleaner,context);

        /* delete childs data*/
        Memory_Delete(list->next);
        list->next = NULL;
    }
}

