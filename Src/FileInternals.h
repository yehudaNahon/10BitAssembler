#ifndef FILE_INTERNALS_H
#define FILE_INTERNALS_H

#include "File.h"
#include <unistd.h>

ssize_t File_GetLine(FILE* file, char** line, size_t* len);


#endif