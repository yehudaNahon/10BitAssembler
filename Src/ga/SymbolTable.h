#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Container.h"
#include "Symbol.h"

/**
    a table for all labels of a type 
*/
typedef struct SymbolTable
{
    size_t count;
    Symbol *elements;
}SymbolTable;

/*
    Initialize a table

    return : a new table
*/
SymbolTable SymbolTable_Init();

/**
    Adds an element to the table

    table - the table to add to the element
    element - the element to add (the element will be copied to a new memory space you do not need to save it)

    return :    true - success
                false - failed
*/
bool SymbolTable_Add(SymbolTable* table,Symbol element);

/**
    Clean all resources of the Symbol Table

    table - the table to delete
*/
void SymbolTable_Delete(SymbolTable* table);

/*
    for each element in the table call the iterator function 

    table - the table to run on
    iter - the iterator to call
    context - some info to send to the iterator each time with the element
*/
void SymbolTable_ForEach(const SymbolTable table, Iterator iter, void* context);


/*
    return the number of elements in the table

    return - the number of elements
*/
size_t SymbolTable_Len(const SymbolTable table);

/*
    return a pointer to the element in the table

    table - the table to get the element from 
    index - the index (from 0-len)

    return - a pointer to the element NULL if failed
*/
Symbol* SymbolTable_GetElement(SymbolTable table, size_t index);


/*
    remove one element from the table

    table - the table to remove the elemnt from 
    index - the index of the element in the table

    return : true - successfully remove the element
             false - failed removing the element
*/
bool SymbolTable_Remove(SymbolTable* table, size_t index);









#endif