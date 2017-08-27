#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "List.h"
#include "Container.h"

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
void File_ForEach(FILE* file,Iterator iter, void* context);

/*
    Write the text to the file

    file : the file descriptor
    text : a null terminated string
    
    return true-success false-falied
*/
bool File_WriteLine(FILE* file,const char* text);

/*
    Create a file and let the iterator write to it using the list elements as data 
    and the file as context

*/
bool File_WriteToFile(char* FileName,List iteratOver,Iterator iter);

/*
    Open a file in append mode ("a") and write data this will keep any data before 
    the open and jst add to it
*/
bool File_AppendToFile(char* FileName,List iteratOver,Iterator iter);

#endif