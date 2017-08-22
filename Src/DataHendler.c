#include <stdio.h>
#include "DataHandler.h"
#include "Log.h"
#include "String.h"
#include "Memory.h"
#include "Convert.h"
#include "Assembly.h"

#define STR_OPEN ('"')
#define STR_CLOSE ('"')


void DataHandler_AddToList(int value, List* bytes)
{
    Byte byte;
    int i=0;

    if(!bytes)
    {
        Log(eError, PARAM_ERR);
        return;
    }

    byte.value = value;
    List_Add(bytes,&byte, sizeof(Byte));
}


size_t DataHandler_StringHandler(char* command, char* params, void* list)
{
    char* ptr = NULL;
    size_t size = 0;

    /* validaty check*/
    if(!params || params[0] != STR_OPEN || params[String_Len(params - 1)] != STR_CLOSE)
    {
        Log(eError,PARAM_ERR);
        return 0;
    }

    for(ptr = &params[1], size = 0; *ptr != STR_CLOSE ; ptr++, size++)
    {
        /*add the string to the list*/
        DataHandler_AddToList(*ptr, list);
    }
    
    /*add null char to the list*/
    DataHandler_AddToList(0, list);
        
    return size;
}


size_t DataHandler_CalculateMatSize(char* mat)
{
    char* numberStr = NULL;
    int size = 1;
    if(!mat)
    {
        Log(eError,PARAM_ERR);
        return 0;
    }
    
    numberStr = String_Split(mat, MAT_CLOSE);
    do
    {
        if(numberStr[0] != MAT_OPEN)
        {
            Log(eError, "Recieved a illigal mat size format");
            return size;
        }
        size *= Convert_StrToDecimal(&numberStr[1]);
    }while((numberStr = String_Split(NULL, MAT_CLOSE)));

    return size;
}


size_t DataHandler_MatHandler(char* command, char* params, void* list)
{
    char* matSize = params;
    char* matVals = NULL;
    size_t size = 0;
    char* valueStr = NULL;
    int value = 0;
    int added=0;

    if(!params || !list)
    {
        Log(eError, PARAM_ERR);
        return 0;
    }

    matVals = String_SplitToTwo(matSize,SPACE_CH);

    size = DataHandler_CalculateMatSize(matSize);
    if(size == 0)
    {
        Log(eError, "Recieved illigal Mat Size Format");
        return 0;
    }

    valueStr = String_Split(matVals,COMMA_STR);
    if(valueStr)
    {
        do
        {
            if(added == size)
            {
                Log(eError, "To Many Values for mat size");
                return size;
            }
            value = Convert_StrToDecimal(valueStr);
            DataHandler_AddToList(value,list);
            added++;
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }

    while(added != size)
    {
        DataHandler_AddToList(0,list);
        added++;
    }

    return size;
}


size_t DataHandler_DataHandler(char* command, char* params, void* list)
{
    size_t size = 0;
    char* valueStr = NULL;
    int value = 0;
    
    if(!params || !list)
    {
        Log(eError, PARAM_ERR);
        return 0;
    }

    valueStr = String_Split(params,COMMA_STR);
    if(valueStr)
    {
        do
        {
            value = Convert_StrToDecimal(valueStr);
            DataHandler_AddToList(value,list);
            size++;
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }
    
    return size;
}


#define DATA_NUM_OF_ELEM (3)
Handler dataHandlers[DATA_NUM_OF_ELEM] = {
    {".data", &DataHandler_DataHandler},
    {".mat", &DataHandler_MatHandler},
    {".string", &DataHandler_StringHandler}
};


bool DataHandler_IsLine(char* command)
{
    return Handler_HasHandler(command, dataHandlers, DATA_NUM_OF_ELEM);
}

size_t DataHandler_Handle(char* command,char* params, List* bytes)
{
    return Handler_Handle(command, params, bytes, dataHandlers, DATA_NUM_OF_ELEM);
}
