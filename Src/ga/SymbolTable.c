#include "SymbolTable.h"
#include "Log.h"
#include "Memory.h"

SymbolTable SymbolTable_Init()
{
    SymbolTable table;
    table.count = 0;
    table.elements = NULL;

    return table;
}

void SymbolTable_Delete(SymbolTable* table)
{
    int i = 0;
    
    /* run on all elements in the table*/
    for(i = 0; i < table->count; i++)
    {
        /* call the deleting function of element and delete the memory block*/
        Symbol_Delete(&table->elements[i]);
        Memory_Delete(&table->elements[i]);
    }

    table->count = 0;
}

bool SymbolTable_Add(SymbolTable* table,Symbol element)
{
    /* validty check*/
    if(!table)
    {
        return false;
    }

    /* 
    locate a new block of memory to for the new element by the Memory.h docs in case there no
    old memory this will create a barnd new element
    */
    table->elements = Memory_ReAllocate(table->elements, sizeof(Symbol) * (table->count + 1));
    if(!table->elements)
    {
        Log(eError, MEMORY_ERR);
        return false;

    }

    /* Initiate the element with the element data*/
    table->elements[table->count] = Symbol_Copy(&element);
    table->count++;

    return true;
}


void SymbolTable_ForEach(const SymbolTable table, Iterator iter, void* context)
{
    size_t i=0;

    for(i=0; i< table.count; i++)
    {
        iter(&table.elements[i],sizeof(Symbol), context);
    }
}

size_t SymbolTable_Len(const SymbolTable table)
{
    return table.count;
}

Symbol* SymbolTable_GetElement(SymbolTable table, size_t index)
{
    if(table.count > index)
    {
        return NULL;
    }

    return &table.elements[index];
}

bool SymbolTable_Remove(SymbolTable* table, size_t index)
{
    if(!table || index > table->count)
    {
        return false;
    }

    Symbol_Delete(&table->elements[index]);
    Memory_Delete(&table->elements[index]);
    
    return true;
}





