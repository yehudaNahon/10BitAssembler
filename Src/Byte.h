
#include <stdint.h>
#include <stddef.h>

/* General for all bytes in the assembly file*/
#define BYTE_LEN (10)


typedef struct Byte
{
    int value :BYTE_LEN;
}Byte;


typedef enum EEncodingType
{
    eAbsolute,
    eExternal,
    eRelocatable
}EEncodingType;

typedef enum EAddressingType
{
    eImmediate,
    eDirect,
    eMetAccess,
    eDirectRegister
}EAddressingType;











