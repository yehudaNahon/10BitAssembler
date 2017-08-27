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
    symbol->dataType = eDataSymbol;
}

Symbol Symbol_Init(char* name, size_t address,ESymbolDataType dataType)
{
    Symbol symbol;
    
    Symbol_Clean(&symbol);

    if(name)
    {
        String_Copy(symbol.name, name, String_Len(name));
    }
    symbol.address = address;
    symbol.type = ePrivate;
    symbol.dataType = dataType;
    return symbol;
}

Symbol Symbol_Copy(Symbol* other)
{
    Symbol symbol = Symbol_Init(other->name, other->address,other->dataType);

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

bool Symbol_Finder(void* symbolPtr, size_t index, void* name)
{
    Symbol* symbol = symbolPtr;
    
    if(String_Compare(symbol->name,name,MAX_SYMBOL_NAME_LEN) == 0)
    {
        return true;
    }

    return false;
}

void Symbol_Print(const void* data,size_t len, void* context)
{
    const Symbol* symbol = data;
    printf("%s : %lu ---- %s :: %s\n",
        symbol->name, symbol->address, symbol->type?"Public":"Private", 
        symbol->dataType == eDataSymbol ? "Data" :(symbol->dataType == eCommandSymbol ? "Command" : "External"));
}