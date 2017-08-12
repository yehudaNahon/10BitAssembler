#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

/**
    Dynamicly allocate new memory

    bytes -     the number of bytes to allocate

    return :    a pointer to the new allocated memory 
                NULL on failur
*/
void* Memory_Allocate(size_t bytes);

/**
    Reallocate memory to a new size the old memory will be copied back to the new one
    In case old is equel to NULL a new block of memory will be allocated

    old -       a pointer to the old memory block
    bytes -     a amount of bytes to allocate and copy to

    return :    a pointer to the new allocated memory 
                NULL on failur
*/
void* Memory_ReAllocate(void* old, size_t bytes);

/**
    Delete dynamicly allocated memory

    memory  -   a pointer to the block of memory to free
*/
void Memory_Delete(void* memory);

/*
    Write to all memory byte value
*/
void Memory_Set(void* mem, uint8_t value, size_t length);

/**
    Copy "length" bytes from mem2 to mem1
*/
size_t Memory_Copy(void* mem1, void* mem2, size_t length);

#endif