#ifndef Byte_TABLE_H
#define Byte_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Container.h"
#include "Byte.h"

/**
    a table for all labels of a type 
*/
typedef struct ByteTable
{
    size_t count;
    Byte *elements;
}ByteTable;

/*
    Initialize a table

    return : a new table
*/
ByteTable ByteTable_Init();

/**
    Adds an element to the table

    table - the table to add to the element
    element - the element to add (the element will be copied to a new memory space you do not need to save it)

    return :    true - success
                false - failed
*/
bool ByteTable_Add(ByteTable* table,Byte element);

/**
    Clean all resources of the Byte Table

    table - the table to delete
*/
void ByteTable_Delete(ByteTable* table);

/*
    for each element in the table call the iterator function 

    table - the table to run on
    iter - the iterator to call
    context - some info to send to the iterator each time with the element
*/
void ByteTable_ForEach(const ByteTable table, Iterator iter, void* context);


/*
    return the number of elements in the table

    return - the number of elements
*/
size_t ByteTable_Len(const ByteTable table);

/*
    return a pointer to the element in the table

    table - the table to get the element from 
    index - the index (from 0-len)

    return - a pointer to the element NULL if failed
*/
Byte* ByteTable_GetElement(ByteTable table, size_t index);


/*
    remove one element from the table

    table - the table to remove the elemnt from 
    index - the index of the element in the table

    return : true - successfully remove the element
             false - failed removing the element
*/
bool ByteTable_Remove(ByteTable* table, size_t index);


#endif