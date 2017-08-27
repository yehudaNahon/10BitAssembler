#include "Symbol.h"
#include "String.h"
#include "Memory.h"
#include <stdio.h>
#include "Convert.h"
#include "Assembly.h"

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

bool Symbol_ExternFinder(void* symbolPtr, size_t index, void* counter)
{
    Symbol* symbol = symbolPtr;
    int* count = counter;
    if(symbol && symbol->address == *count)
    {
        return true;
    }

    return false;
}

void Symbol_Print(void* data,size_t len, void* context)
{
    char buffer[MAX_LINE_LEN];
    const Symbol* symbol = data;

    Memory_Set(buffer,0,sizeof(buffer));
    Convert_DecimalToBase4Str(symbol->address,buffer,sizeof(buffer),4);

    printf("%s : %s ---- %s :: %s\n",
        symbol->name,buffer, symbol->type?"Public":"Private", 
        symbol->dataType == eDataSymbol ? "Data" :(symbol->dataType == eCommandSymbol ? "Command" : "External"));
}

void Symbol_UpdateDataSymbolAddressIter(void* symbolPtr, size_t index, void* baseAddressPtr)
{
    Symbol* symbol = symbolPtr;
    int *toAdd = (int*)baseAddressPtr;
    if(symbol && symbol->dataType == eDataSymbol)
    {
        symbol->address += *toAdd; 
    }
}



