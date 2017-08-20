#include "Memory.h"

#include <string.h>
#include <malloc.h>

void* Memory_Allocate(size_t bytes)
{
    return malloc(bytes);
}

void* Memory_ReAllocate(void* old, size_t newLength)
{
    return realloc(old, newLength);
}

void Memory_Delete(void* memory)
{
    free(memory);
}

void Memory_Set(void* mem,  uint8_t value, size_t length)
{
    memset(mem, value, length);
}

size_t Memory_Copy(void* mem1,const  void* mem2, size_t length)
{
    /* validaty check*/
    if(!mem1 || !mem2)
    {
        return 0;
    }

    /* cpoy memory*/
    memcpy(mem1, mem2, length);

    return length;
}
