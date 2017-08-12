#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>


/*
    Open a file descriptor
*/
FILE* File_Open(const char* fileName, const char* mode);

/*
    Close a file descriptor
*/
bool File_Close(FILE* file);

/*
	Return the file name clean from its type
*/
bool File_CleanName(const char* fileName, char* o_rawName, int length);

/*
	Copies the file name and extansion to the buffer  	
*/
void File_CreateName(const char *name,const char* extension,char* o_buff, size_t bufferLen);

/*
    return a pointer to the dot position in the file name
*/
char* File_FindDot(const char* fileName);

/*
    Iterate over all lines of a file

    file        - a file descriptor to read
    iterator    - a iterator object that run on all the file lines and recieves:
                     -the line terminated by a null character in a ascii format  
                    -the lines index from 0 
                    -a pointer to a user selected data structure that will be passed with context
    context     - a pointer to user selected data structure to pass at each line call
*/
bool File_ForEachLine(FILE* file, void (*iterator)(char*,size_t,void*), void* context);




#endif