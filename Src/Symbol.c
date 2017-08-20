#include "Symbol.h"
#include "SymbolInternals.h"
#include "String.h"
#include "Memory.h"
#include <stdio.h>

void Symbol_Clean(Symbol* symbol)
{
    Memory_Set((void*)symbol->name, 0, sizeof(symbol->name));
    symbol->address = 0;
    symbol->type = ePrivate;
}

Symbol Symbol_Init(char* name, size_t address)
{
    Symbol symbol;
    
    Symbol_Clean(&symbol);

    if(name)
    {
        String_Copy(symbol.name, name, String_Len(name));
    }
    symbol.address = address;
    symbol.type = ePrivate;

    return symbol;
}

Symbol Symbol_Copy(Symbol* other)
{
    Symbol symbol = Symbol_Init(other->name, other->address);

    Symbol_ChangeType(&symbol,other->type);

    return symbol;
}

void Symbol_ChangeType(Symbol* symbol,ESymbolType type)
{
    symbol->type = type;
}


void Symbol_Delete(Symbol* symbol)
{
    Symbol_Clean(symbol);   
}