#ifndef IMMEDIATE_H
#define IMMEDIATE_H

#include "List.h"

bool IsImmediate(const char* immediate);

bool AddImmediate(const char* immediate,List* bytes);

size_t SizeImmediate();



#endif