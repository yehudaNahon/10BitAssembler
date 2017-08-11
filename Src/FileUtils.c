#include <string.h>
#include "FileUtils.h"
#include "GeneralMacros.h"

#define DIVIDER_CH ('.')


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
