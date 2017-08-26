#include "MatOperandHandler.h"
#include "MatOperandHandlerInternals.h"
#include "LabelOperandHandler.h"
#include "RegOperandHandler.h"
#include "String.h"
#include "Assembly.h"



Handler MatOperandHandler = {
    &MatOPerandHandler_IsHandler,
    &MatOPerandHandler_GetSize,
    &MatOPerandHandler_Add,
};  


size_t MatOPerandHandler_GetSize(const char* param)
{
    return 2;
}


bool MatOPerandHandler_IsHandler(const char* param)
{
    char buffer[MAX_LINE_LEN];
    char* ptr = NULL;
    char* mat = NULL;
    
    /* validaty check*/
    if(!param)
    {
        return false;
    }
    
    String_Copy(buffer, param, MAX_LINE_LEN);
    
    /* locate the mat []*/
    mat = String_SplitToTwo(buffer, MAT_OPEN);
    if(!mat)
    {
        return false;
    }
    
    /*check the place is a valid label*/
    if(!LabelOperandHandler.IsHandler(buffer))
    {
        return false;
    }
    
    /* check all mat params are valid registers*/
    ptr = String_Split(mat, MAT_CLOSE);
    do
    {
        if(ptr[0] == MAT_OPEN)
        {
            ptr++;
        }
        if(!RegOperandHandler.IsHandler(ptr))
        {
            return false;
        }
    }while((ptr = String_Split(NULL, MAT_CLOSE)));
    
    return true;
}



bool MatOPerandHandler_Add(const char* operand,List* bytes,List symbols)
{
    char buffer[MAX_LINE_LEN];
    char* ptr = NULL;
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
    if(!LabelOperandHandler.IsHandler(label))
    {
        return false;
    }
    
    if(!LabelOperandHandler.Add(label,bytes, symbols))
    {
        return false;
    }

    /* check all mat params are valid registers*/
    ptr = String_Split(mat, MAT_CLOSE);
    do
    {
        if(ptr[0] == MAT_OPEN)
        {
            ptr++;
        }
        if(!RegOperandHandler.IsHandler(ptr))
        {
            return false;
        }
        if(!RegOperandHandler.Add(ptr,bytes,symbols))
        {
            return false;
        }
    }while((ptr = String_Split(NULL, MAT_CLOSE)) && ptr[0] == MAT_OPEN);
    
    return true;
}
