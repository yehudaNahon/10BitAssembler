#ifndef ASSEMBLER_INTERNALS_H
#define ASSEMBLER_INTERNALS_H

#include "Assembler.h"
#include <stddef.h>

void Assembler_AddLine(char* line, size_t index,void* programme);

void Assembler_IsLabel(char* word, size_t index, void* programme);

bool Assembler_IsCodeLine(char* line);

void Assembler_CleanLine(char* line);

#endif
