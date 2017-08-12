#include "SymbolTable.h"
#include "Log.h"
#include "Memory.h"

SymbolTable SymbolTable_Init()
{
    SymbolTable table;
    table.count = 0;
    table.symbols = NULL;

    return table;
}

void SymbolTable_Delete(SymbolTable* table)
{
    int i = 0;
    
    /* run on all symbols in the table*/
    for(i = 0; i < table->count; i++)
    {
        /* call the deleting function of symbol and delete the memory block*/
        Symbol_Delete(&table->symbols[i]);
        Memory_Delete(&table->symbols[i]);
    }

    table->count = 0;
}


SymbolTable SymbolTable_Copy(SymbolTable* other)
{
    SymbolTable this = SymbolTable_Init();
    int i = 0;

    for(i=0; i< other->count; i++)
    {
        SymbolTable_AddSymbol(&this, &other->symbols[i]);
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
