#ifndef SYMBOL_H
#define SYMBOL_H

#include <stddef.h>
#include <stdbool.h>


#define MAX_SYMBOL_NAME_LEN (80)

typedef enum ESymbolType
{
    ePrivate,
    ePublic
}ESymbolType;

typedef enum ESymbolDataType
{
    eDataSymbol,
    eCommandSymbol,
    eExternalSymbol
}ESymbolDataType;

/*
    A data structure containing a single symbol each symbol is represented by a name and 
    linked into an address in memory
*/
typedef struct Symbol
{
    char name[MAX_SYMBOL_NAME_LEN];
    size_t address;
    ESymbolType type;
    ESymbolDataType dataType; 
}Symbol; 


Symbol Symbol_Init(char* name, size_t address,ESymbolDataType type);

Symbol Symbol_Copy(Symbol* oldSymbol);

void Symbol_ChangeType(Symbol* symbol,ESymbolType type);

void Symbol_Delete(Symbol* symbol);


bool Symbol_Finder(void* symbolPtr, size_t index, void* name);

void Symbol_Print(const void* data,size_t len, void* context);


#endif