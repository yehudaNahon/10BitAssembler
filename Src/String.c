#include "String.h"
#include "Memory.h"
#include "Log.h"
#include <string.h>
#include <stdio.h>
#define WASTE_STR (" \r\n\t")
#define SPACE_STR (" ")

int String_Len(const char* str)
{
    return str ? strlen(str) : -1;
}

bool String_HasChar(const char* str, char ch)
{
    return String_FindChar(str,ch) != NULL;
}

char* String_FindChar(const char* str, char ch)
{
    return strchr(str,ch);
}

void String_Copy(char* dst,const char* src, int maxLen)
{
    strncpy(dst, src, maxLen);
}

void String_Append(char* dst, const char* src, int maxLen)
{
    strncat(dst, src, maxLen);
}


char* String_Split(char* str, const char* delimiter)
{
    return strtok(str,delimiter);
}

char* String_SplitToTwo(char* str,char ch)
{
    char* ptr = strchr(str,ch);
    if(!ptr || String_Len(str) == (ptr - str))
    {
        return NULL;
    }

    *ptr = 0;
    ptr++;

    return ptr;
}

bool String_OnlyWithChars(char* word, char* chars)
{
    /* if the length of the segment with the valid chars is the same as the intire length then its only with this chars*/
    return strspn(word,chars) == strlen(word);
}

size_t String_SubString(char* str,char* buffer, size_t begin, size_t count)
{
    if(!str || !buffer || begin + count > String_Len(str))
    {
        return 0;
    }

    return Memory_Copy(buffer,&str[begin],count);
}

int String_Compare(const char* str1, const char* str2, size_t maxLen)
{
    return strncmp(str1, str2, maxLen);
}


/* cleans the line from un needed spaces and tabs*/
void String_SimplfyLine(char* line)
{
    char* word = NULL;

    if(!line)
    {
        return;
    }
    /*create buffer in the line size plus null*/
    size_t length = String_Len(line + 1);
    char* buffer = (char*)Memory_Allocate(length);
    if(!buffer)
    {
        Log(eError,MEMORY_ERR);
    }
    /*clean buffer*/
    Memory_Set(buffer,0,length);

    /* spite to single words and create a new sentence only with the basic signs*/
    word = String_Split(line, WASTE_STR);
    /* if theres no words*/
    if(!word)
    {
        /*cleanup and exit*/
        Memory_Delete(buffer);
        Memory_Copy(line,buffer,length);
        return;
    }

    do
    {
        String_Append(buffer,word,length);
        String_Append(buffer,SPACE_STR,length);
    }while((word = String_Split(NULL, WASTE_STR)));

 
    /* copy back the info to line*/
    String_Copy(line,buffer,length);
    /*release resources*/
    Memory_Delete(buffer);
}

/*
    print the line given to stdout
*/
void String_PrintLine(void* line, size_t* len, void* context)
{
    String_SimplfyLine(line);
    printf("%s\n",(char*)line);
}


bool String_Empty(const char* line)
{
    return line ? line[0] == 0 || line[0] == '\n' : true;
}


