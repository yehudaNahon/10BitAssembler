#ifndef ENTRY_HANDLER_H
#define ENTRY_HANDLER_H 

#include "Handler.h"

extern Handler EntryHandler;

bool WriteEntryFile(char fileName[],List* symbols);

#endif