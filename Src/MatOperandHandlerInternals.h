#ifndef MAT_OPERAND_HANDLER_INTERNALS_H
#define MAT_OPERAND_HANDLER_INTERNALS_H

#include "MatOperandHandler.h"

#define MAT_OPEN ('[')
#define MAT_CLOSE ("]")


bool MatOPerandHandler_IsHandler(const char* param);

size_t MatOPerandHandler_GetSize(const char* param);

bool MatOPerandHandler_Add(const char* operand,List* bytes,List symbols);




#endif