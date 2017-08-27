#ifndef ENTRY_HANDLER_H
#define ENTRY_HANDLER_H 

#include "Handler.h"

/*
    a handler struct for all handler functions
*/
extern Handler EntryHandler;

/*
    Create a entry file with all the entry symbols of the programme 
*/
bool WriteEntryFile(char fileName[],List* symbols);

#endif