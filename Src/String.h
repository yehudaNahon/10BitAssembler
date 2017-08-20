#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stddef.h>

#define LETTERS_CH "abcdefghijklmnopqrstuvwxyz"
#define UPPER_CASE_CH "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMBERS_CH "1234567890"
#define SPACE_CH (' ')


int String_Len(const char* str);

bool String_HasChar(const char* str,char ch);

bool String_HasOneOfChars(const char* str, char ch);

char* String_FindChar(const char* str, char ch);

void String_Copy(char* dst,const char* src, int maxLen);

void String_Append(char* dst, const char* src, int maxLen);

char* String_Split(char* str, const char* delimiter);

char* String_SplitToTwo(char* str,char ch);

bool String_OnlyWithChars(char* word,char* chars);

/*
    compare between 2 strings characters till maxLen or till NULL char

    return : -1 - str1 is dictionarly gratter then str2
             0  - the strings are the same
             1  - str2 is dictionarly gratter then str1
*/
int String_Compare(const char* str1, const char* str2, size_t maxLen);

void String_SimplfyLine(char* line);

bool String_Empty(const char* line);


#endif