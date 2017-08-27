#include "Memory.h"
#include "BitArray.h"
#include <stdio.h>
#include "Byte.h"

/* sets the bit at k index to its opisit value*/
#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )

/* sets the bit at k index to 0 value*/
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )

/*returns the bits at k index value*/
#define GetBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )


void PrintBits(uint8_t bytes[],size_t numOfBits)
{
    int i;
    for(i=numOfBits - 1;i >= 0 ;i--)
    {
        printf("%s",GetBit(bytes,i) ? "1" : "0");
    }
}

void PrintBitsIter(const void* data,size_t len,void* context)
{
    uint8_t *bytes = Memory_Allocate(len);

    Memory_Copy(bytes,data,len);

    PrintBits(bytes,10);

    printf("\n");

    Memory_Delete(bytes);
}


