#include <stdio.h>
#include "DataHandler.h"
#include "Log.h"
#include "String.h"
#include "Memory.h"
#include "Convert.h"

#define STR_OPEN ('"')
#define STR_CLOSE ('"')


void DataHandler_AddToTable(int value, ByteTable* table)
{
    Byte byte;
    int i=0;

    if(!table)
    {
        Log(eError, PARAM_ERR);
        return;
    }

    byte.value = value;
    ByteTable_Add(table,byte);
}


size_t DataHandler_StringHandler(char* params, void* table)
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
        /*add the string to the table*/
        DataHandler_AddToTable(*ptr, table);
    }
    
    /*add null char to the table*/
    DataHandler_AddToTable(0, table);
        
    return size;
}


#define MAT_OPEN ('[')
#define MAT_CLOSE ("]")
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


#define COMMA_STR (",")
size_t DataHandler_MatHandler(char* params, void* table)
{
    char* matSize = params;
    char* matVals = NULL;
    size_t size = 0;
    char* valueStr = NULL;
    int value = 0;
    int added=0;

    if(!params || !table)
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
            DataHandler_AddToTable(value,table);
            added++;
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }

    while(added != size)
    {
        DataHandler_AddToTable(0,table);
        added++;
    }

    return size;
}


size_t DataHandler_DataHandler(char* params, void* table)
{
    size_t size = 0;
    char* valueStr = NULL;
    int value = 0;
    
    if(!params || !table)
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
            DataHandler_AddToTable(value,table);
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

size_t DataHandler_Handle(char* command,char* params, ByteTable* table)
{
    return Handler_Handle(command, params, table, dataHandlers, DATA_NUM_OF_ELEM);
}
