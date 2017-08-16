
#include <stddef.h>


typedef struct Table
{
    size_t count;
    size_t maxLen;
    void** array;
}Table;

Table Table_Init(size_t maxElementLength);


Table Table_Copy(Table* other);

bool Table_AddElement(Table* table,void* element,size_t length);

size_t Table_GetElement(Table* table, size_t index, void* o_element);

bool Table_RemoveElement(Table* table, size_t index, void* o_element);

void Table_Print(Table* table);

void Table_Delete(Table* table, void (*Cleaner)(void*));







