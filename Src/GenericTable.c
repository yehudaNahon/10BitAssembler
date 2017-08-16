#include "GenericTable.h"
#include "Log.h"
#include "Memory.h"

Table Table_Init(size_t maxElementLength)
{
    Table table;
    table.count = 0;
    table.maxLen = maxElementLength;
    table.array = NULL;

    return table;
}

void Table_Delete(Table* table, void (*Cleaner)(void*))
{
    int i = 0;
    
    /* run on the array*/
    for(i = 0; i < table->count; i++)
    {
        /* call the deleting function of symbol and delete the memory block*/
        Cleaner(&table->array[i]);
        Memory_Delete(&table->array[i]);
    }

    table->count = 0;
}


Table Table_Copy(Table* other)
{
    Table this = Table_Init(other->maxLen);
    int i = 0;

    for(i=0; i< other->count; i++)
    {
        Table_AddElement(&this, &other->array[i],);
    }

    return this;
}

void SymbolTable_Print(SymbolTable* table)
{
    int i=0;

    for(i=0; i<table->count; i++)
    {
        Symbol_Print(&table->symbols[i]);
    }
}


bool SymbolTable_AddSymbol(SymbolTable* table,Symbol* symbol)
{
    /* validty check*/
    if(!table || !symbol)
    {
        return false;
    }

    /* 
    locate a new block of memory to for the new symbol by the Memory.h docs in case there no
    old memory this will create a barnd new symbol
    */
    table->symbols = Memory_ReAllocate(table->symbols, sizeof(Symbol) * (table->count + 1));
    if(!table->symbols)
    {
        Log(eError, MEMORY_ERR);
        return false;

    }

    /* Initiate the symbol with the symbol data*/
    table->symbols[table->count] = Symbol_Copy(symbol);
    table->count++;

    return true;
}
