#include <stdlib.h>
#include <stddef.h>

#include "File.h"
#include "FileInternals.h"
#include "String.h"
#include "GeneralMacros.h"

#define DOT_CH ('.')
#define FD_ERROR (-1)


FILE* File_Open(const char* fileName, const char* mode)
{
	return fopen(fileName, mode);
}

bool File_Close(FILE* file)
{
	return fclose(file) != EOF;
}

bool File_CleanName(const char* fileName, char* o_rawName, int length)
{
	char* ptr = NULL;

	if(fileName == NULL || o_rawName == NULL)
	{
		return false;
	}
     
    ptr = File_FindDot(fileName);

	/* check if only the name was specified*/
	if(!ptr)
	{
		String_Copy(o_rawName, fileName, MIN(String_Len(fileName),length));
	}
	else
	{
		/* calculate the offset from the point by subtracting the ptr from the base pointer*/
		String_Copy(o_rawName, fileName, MIN((int)(ptr - fileName),length));
	}

	return true;
}


void File_CreateName(const char *name,const char* extension,char* o_buff, size_t bufferLen)
{
	String_Copy(o_buff, name, bufferLen);
	String_Append(o_buff, extension, bufferLen - String_Len(name));
}

char* File_FindDot(const char* fileName)
{
	return String_FindChar(fileName, DOT_CH);
}


bool File_ForEachLine(FILE* file, void (*iterator)(char*,size_t,void*), void* context)
{
    char* line = NULL;
    size_t len = 0;
    size_t lineCount = 0;

    /* validaty check*/
    if(!file || !iterator)
    {
        return false;
    }

    /* run on all lines and call the iterator*/
    lineCount = 0;
    while (File_GetLine(file, &line, &len) != FD_ERROR) {
        iterator(line,lineCount,context);
        lineCount++;
    }

    return true;
}

ssize_t File_GetLine(FILE* file, char** line, size_t* len)
{
	return getline(line, len, file);
}

