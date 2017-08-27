#include <stdlib.h>
#include <stddef.h>
#include "Log.h"
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


void File_ForEach(FILE* file,Iterator iter, void* context)
{
    char* line = NULL;
    size_t len = 0;
    size_t lineCount = 0;

    /* run on all lines and call the iterator*/
	if(file && iter)
	{
		lineCount = 0;
		while (File_GetLine(file, &line, &len) != FD_ERROR) {
			iter(line,len,context);
			lineCount++;
		}
	}
}

ssize_t File_GetLine(FILE* file, char** line, size_t* len)
{
	return getline(line, len, file);
}

bool File_WriteLine(FILE* file,const char* text)
{
	if(!file || !text)
	{
		return false;
	}

	fprintf(file,"%s\n",text);

	return true;
}

bool File_WriteToFile(char* entryFileName,List iteratOver,Iterator iter)
{
    /*open the file*/
    FILE* file = File_Open(entryFileName, "w+");
    
    if(!file)
    {
        Log(eError,"Could not open file");
        return false;
    }

    List_ForEach(iteratOver,iter,file);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }    
}
