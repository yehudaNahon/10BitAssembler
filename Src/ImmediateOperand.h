#ifndef IMMEDIATE_H
#define IMMEDIATE_H

#include "List.h"

/*
    return wether or not the line is a immediate operand
*/
bool IsImmediate(const char* immediate);

/*
    add the line to the list as a immediate operand
*/
bool AddImmediate(const char* immediate,List* bytes);

/*
    return the size of the immediate operand
*/
size_t SizeImmediate();



#endif