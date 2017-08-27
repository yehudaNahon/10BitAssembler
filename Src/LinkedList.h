#ifndef LinkedList_H
#define LinkedList_H

#include <stddef.h>
#include <stdbool.h>
#include "Container.h"

/*
    A linked list data structure node
*/
typedef struct LinkedList
{
    size_t length;
    void* data;
    struct LinkedList* next;    
}LinkedList;

/*
    initiate a new linked list
*/
LinkedList LinkedList_Init();

/*
    get the data in element of index 

    return : the size of the returned element 0 for fail
*/
size_t LinkedList_Get(LinkedList list, size_t index,void* o_data);

/*
    adds a new element to the list with data in size length

    note:   the element is directly copied to a new dynamicly allocated place
            so do not worry about stack variables but do reallocate inner pointer
*/
bool LinkedList_Add(LinkedList* list,const void* data, size_t length);

/*
    returns the len of the list
*/
size_t LinkedList_Len(LinkedList list);

/*
    removes a element finded by the finder function and returnes it in o_data

    return - the size of the data 0 if no data was found
*/
size_t LinkedList_Remove(LinkedList* list,void* o_data, Finder finder,void* context);

/*
    finds data in the linked list using the finder function
*/
size_t LinkedList_FindData(LinkedList list, void** o_data,Finder finder,void* context);

/*
    calls iterator for each elements data in the list
*/
void LinkedList_ForEach(LinkedList list,Iterator iter, void* context);


/*
    deletes the entier linked list 
    note : each element will be passed to cleaner before release for inner dynamic memory release
*/
void LinkedList_Delete(LinkedList* list ,Cleaner cleaner,void* context);

/* 
    appends list src to list dst
    note :  all the elements will be added by value and not by refernce so dont forget to delete 
            the old list after you finish
*/
bool LinkedList_Append(LinkedList* dst,LinkedList* src);

#endif