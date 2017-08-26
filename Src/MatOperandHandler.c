#include "MatOperandHandler.h"
#include "LabelOperandHandler.h"
#include "RegOperandHandler.h"
#include "String.h"
#include "Assembly.h"
#include <stdio.h>


#define MAT_OPEN ('[')
#define MAT_CLOSE (']')


bool IsMat(const char* operand)
{
    char buffer[MAX_LINE_LEN];
    char* ptr = NULL;
    char* reg1;
    char* reg2;
    char* label = buffer;
    char* mat = NULL;
    /* validaty check*/
    if(!operand)
    {
        return false;
    }
    
    String_Copy(buffer, operand, MAX_LINE_LEN);
    
    /* locate the mat []*/
    mat = String_SplitToTwo(buffer, MAT_OPEN);
    label = buffer;
    if(!mat)
    {
        return false;
    }
    
    /*check the place is a valid label*/
    if(!IsLabel(label))
    {
        return false;
    }

    /* check all mat params are valid registers*/
    reg2 = String_SplitToTwo(mat, MAT_CLOSE);
    reg1 = mat;
    
    if(reg2[0] != MAT_OPEN)
    {
        return false;
    }

    reg2++;
    String_SplitToTwo(reg2, MAT_CLOSE);
    
    if(!IsReg(reg1) || !IsReg(reg2))
    {
        return false;
    }
    
    return true;
}

bool AddMat(const char* operand,List* bytes,List* symbols)
{
    char buffer[MAX_LINE_LEN];
    char* ptr = NULL;
    char* reg1;
    char* reg2;
    char* label = buffer;
    char* mat = NULL;
    /* validaty check*/
    if(!operand)
    {
        return false;
    }
    
    String_Copy(buffer, operand, MAX_LINE_LEN);
    
    /* locate the mat []*/
    mat = String_SplitToTwo(buffer, MAT_OPEN);
    label = buffer;
    if(!mat)
    {
        return false;
    }
    
    /*check the place is a valid label*/
    if(!IsLabel(label))
    {
        return false;
    }
    
    if(!AddLabel(label,bytes, symbols))
    {
        return false;
    }



    /* check all mat params are valid registers*/
    reg2 = String_SplitToTwo(mat, MAT_CLOSE);
    reg1 = mat;
    
    if(reg2[0] != MAT_OPEN)
    {
        return false;
    }

    reg2++;
    String_SplitToTwo(reg2, MAT_CLOSE);
    
    if(!IsReg(reg1) || !IsReg(reg2))
    {
        return false;
    }
    if(!AddRegs(reg1,reg2,bytes))
    {
        return false;
    }
    return true;
}

size_t SizeMat()
{
    return 2;
}