#ifndef LABEL_OPERAND_HANDLER_INTERNALS_H
#define LABEL_OPERAND_HANDLER_INTERNALS_H

#include "LabelOperandHandler.h"

#define MAX_LABEL_LEN (30)


bool LabelOperandHandler_IsHandler(const char* param);

size_t LabelOperandHandler_GetSize(const char* param);

bool LabelOperandHandler_Add(const char* operand,List* bytes,List* symbols);




#endif