#ifndef SYMBOL_H
#define SYMBOL_H

#include <stddef.h>
#include <stdbool.h>


#define MAX_SYMBOL_NAME_LEN (80)

/*
    the type of the symbol in the programme 
    public for advertised
    private for internal
*/ 
typedef enum ESymbolType
{
    ePrivate,
    ePublic
}ESymbolType;

/*
    the data type the symbol pointes to
*/
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

/*
    initialize a new symbol
*/
Symbol Symbol_Init(char* name, size_t address,ESymbolDataType type);

/*
    copies a symbols to a new buffer
    including all the inner elements reallocation properly
*/
Symbol Symbol_Copy(Symbol* oldSymbol);

/*
    changes the symbols type
*/
void Symbol_ChangeType(Symbol* symbol,ESymbolType type);

/*
    deletes a symbol
*/
void Symbol_Delete(Symbol* symbol);

/*
    a finder function to find a matching symbol in a container by the name
*/
bool Symbol_Finder(void* symbolPtr, size_t index, void* name);

/*
    a finder function to find a extern symbols by the address count
*/
bool Symbol_ExternFinder(void* symbolPtr, size_t index, void* count);

/*
    a iterator for opdating all the symbols in a container by adding to each the base address
*/
void Symbol_UpdateDataSymbolAddressIter(void* symbolPtr, size_t index, void* baseAddressPtr);

/*
    a iterator for printing all the symbols in a container
*/
void Symbol_Print(void* data,size_t len, void* context);


#endif