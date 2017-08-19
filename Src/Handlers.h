#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "Handler.h"

extern Handler commandHandlers[];
#define COMMAND_NUM_OF_ELEM (16)

extern Handler dataHandlers[];
#define DATA_NUM_OF_ELEM (3)

size_t DataHandlers_Data(char* params, void* context);

size_t DataHandlers_Mat(char* params, void* context);

size_t DataHandlers_String(char* params, void* context);

size_t Handler_MOV(char* params,void* context);

size_t Handler_CMP(char* params,void* context);

size_t Handler_ADD(char* params,void* context);

size_t Handler_SUB(char* params,void* context);

size_t Handler_NOT(char* params,void* context);

size_t Handler_CLR(char* params,void* context);

size_t Handler_LEA(char* params,void* context);

size_t Handler_INC(char* params,void* context);

size_t Handler_DEC(char* params,void* context);

size_t Handler_JMP(char* params,void* context);

size_t Handler_BNE(char* params,void* context);

size_t Handler_RED(char* params,void* context);

size_t Handler_PRN(char* params,void* context);

size_t Handler_JSR(char* params,void* context);

size_t Handler_RTS(char* params,void* context);

size_t Handler_STOP(char* params,void* context);





#endif