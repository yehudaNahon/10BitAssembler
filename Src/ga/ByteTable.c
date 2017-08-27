#include "ByteTable.h"
#include "Log.h"
#include "Memory.h"

ByteTable ByteTable_Init()
{
    ByteTable table;
    table.count = 0;
    table.elements = NULL;

    return table;
}

void ByteTable_Delete(ByteTable* table)
{
    int i = 0;
    
    /* run on all elements in the table*/
    for(i = 0; i < table->count; i++)
    {
        /* call the deleting function of element and delete the memory block*/
        Memory_Delete(&table->elements[i]);
    }

    table->count = 0;
}

bool ByteTable_Add(ByteTable* table,Byte element)
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
    table->elements = Memory_ReAllocate(table->elements, sizeof(Byte) * (table->count + 1));
    if(!table->elements)
    {
        Log(eError, MEMORY_ERR);
        return false;

    }

    /* Initiate the element with the element data*/
    table->elements[table->count] = element;
    table->count++;

    return true;
}


void ByteTable_ForEach(const ByteTable table, Iterator iter, void* context)
{
    size_t i=0;

    for(i=0; i< table.count; i++)
    {
        iter(&table.elements[i],sizeof(Byte), context);
    }
}

size_t ByteTable_Len(const ByteTable table)
{
    return table.count;
}

Byte* ByteTable_GetElement(ByteTable table, size_t index)
{
    if(table.count > index)
    {
        return NULL;
    }

    return &table.elements[index];
}

bool ByteTable_Remove(ByteTable* table, size_t index)
{
    if(!table || index > table->count)
    {
        return false;
    }

    Memory_Delete(&table->elements[index]);
    
    return true;
}





