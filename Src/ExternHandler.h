#ifndef EXTERN_HANDLER_H
#define EXTERN_HANDLER_H

#include "Handler.h"

extern Handler ExternHandler;

/*
    Create a extern file with the extern symbols in it
*/
bool WriteExternFile(char* fileName,List* bytes,List* symbols,int baseAddress);

#endif