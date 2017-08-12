#include "String.h"

#include <string.h>


int String_Len(const char* str)
{
    return strlen(str);
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

bool String_OnlyWithChars(char* word, char* chars)
{
    /* if the length of the segment with the valid chars is the same as the intire length then its only with this chars*/
    return strspn(word,chars) == strlen(word);
}


int String_Compare(const char* str1, const char* str2)
{
    return strcmp(str1,str2);
}






