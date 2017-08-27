#ifndef EXTERN_HANDLER_H
#define EXTERN_HANDLER_H

#include "Handler.h"

extern Handler ExternHandler;

bool WriteExternFile(char* fileName,List* bytes,List* symbols,int baseAddress);

#endif