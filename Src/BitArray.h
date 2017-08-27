#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>
#include <stddef.h>
#include "List.h"

/* 
    Prints the contents of the array for len num of bits
*/
void PrintBits(uint8_t bytes[],size_t len);

/*
    Iterate over a list and print the contents in binary
*/
void PrintBitsIter(const void* data,size_t len,void* context);


#endif