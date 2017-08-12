#include <stddef.h>

struct List
{
    size_t count;
    void* elem;
};

List List_Init();

size_t List_AddElement();


