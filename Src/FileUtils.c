#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "FileUtils.h"
#include "GeneralMacros.h"

#define DIVIDER_CH ('.')
#define FD_ERROR (-1)

bool CleanFileName(const char* fileName, char* o_rawName, int length)
{
	char* ptr = NULL;

	if(fileName == NULL || o_rawName == NULL)
	{
		return false;
	}
     
    ptr = FindTypeSplitCharacter(fileName);

	/* check if only the name was specified*/
	if(!ptr)
	{
		strncpy(o_rawName, fileName, MIN(strlen(fileName),length));
	}
	else
	{
		/* calculate the offset from the point by subtracting the ptr from the base pointer*/
		strncpy(o_rawName, fileName, MIN((int)(ptr - fileName),length));
	}

	return true;
}


void CreateFileName(const char *name,const char* extension,char* o_buff, size_t bufferLen)
{
	strncpy(o_buff, name, bufferLen);
	strncat(o_buff, extension, bufferLen - strlen(name));
}

char* FindTypeSplitCharacter(const char* fileName)
{
    return strchr(fileName,DIVIDER_CH);
}


bool ForEachLine(FILE* file, void (*iterator)(char*,size_t,void*), void* context)
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
    while (getline(&line, &len, file) != FD_ERROR) {
        iterator(line,lineCount,context);
        lineCount++;
    }

    return true;
}
