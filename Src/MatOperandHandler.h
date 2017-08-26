#ifndef MAT_OPERAND_HANDLER_H
#define MAT_OPERAND_HANDLER_H

#include "Handler.h"

extern Handler MatOperandHandler;

bool IsMat(const char* mat);

bool AddMat(const char* mat,List* bytes,List* symbols);

size_t SizeMat();


#endif