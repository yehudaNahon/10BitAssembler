#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include <stddef.h>


/*
	Return the file name clean from its type
*/
bool CleanFileName(const char* fileName, char* o_rawName, int length);

/*
	Copies the file name and extansion to the buffer  	
*/
void CreateFileName(const char *name,const char* extension,char* o_buff, size_t bufferLen);

char* FindTypeSplitCharacter(const char* fileName);


#endif