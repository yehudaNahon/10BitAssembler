
#include <stddef.h>

/*
    converts a stirng representing a decimal number to its int value counter part
    note : supports negativ numbers
*/
int Convert_StrToDecimal(const char* str);

/*
    return the number if a string of base 4 of the programme
*/
void Convert_DecimalToBase4Str(int num,char* buffer,size_t len,size_t numOfDigits);


