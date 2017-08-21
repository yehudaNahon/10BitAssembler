#ifndef TYPE_HANDLER_H
#define TYPE_HANDLER_H

#include "LinkedList.h"
#include "SymbolTable.h"
#include "ByteTable.h"
#include <stddef.h>

typedef struct TypeHandler
{
    LinkedList* handlers;
    SymbolTable symbol;
    ByteTable memory;
    size_t counter;
}TypeHandler;


TypeHandler_Init();




#endif