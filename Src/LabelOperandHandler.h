#ifndef LABEL_H
#define LABEL_H

#include "Handler.h"

bool IsLabel(const char* label);

bool AddLabel(char* label,List* bytes,List symbols);

size_t SizeLabel();

#endif