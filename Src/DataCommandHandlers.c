#include "DataCommandHandlers.h"
#include "DataCommandHandlersInternals.h"
#include "Byte.h"
#include "Convert.h"
#include "String.h"
#include "Log.h"
#include "GeneralMacros.h"
#include <stdio.h>

Handler MatCommandHandler = {
    &MatCommandHandler_IsHandler,
    &MatCommandHandler_GetSize,
    &MatCommandHandler_Add,
};

Handler StringCommandHandler = {
    &StringCommandHandler_IsHandler,
    &StringCommandHandler_GetSize,
    &StringCommandHandler_Add
};

Handler DataCommandHandler = {
    &DataCommandHandler_IsHandler,
    &DataCommandHandler_GetSize,
    &DataCommandHandler_Add
};


bool DataUtils_GetCommand(const char* line, char* buffer,size_t len)
{
    String_Copy(buffer,line,len);
    return String_SplitToTwo(buffer,SPACE_CH) != NULL;
}

char* DataUtils_GetParams(const char* line)
{
    return String_FindChar(line,SPACE_CH) + 1;
}

bool DataUtils_IsCommand(const char* commandStr,const char* command)
{
    if(!commandStr || !command)
    {
        return false;
    }

    return String_Compare(commandStr,command,MIN(String_Len(command),String_Len(commandStr))) == 0;
}


bool StringCommandHandler_Add(const char* line, List* bytes,List* symbols)
{
    Byte byte;
    const char* params = DataUtils_GetParams(line);
    const char* ptr = NULL;
    size_t size = 0;

    /* validaty check*/
    if(!params || params[0] != STR_OPEN || params[String_Len(params) - 1] != STR_CLOSE)
    {
        Log(eError,PARAM_ERR);
        return false;
    }

    for(ptr = &params[1], size = 0; *ptr != STR_CLOSE ; ptr++, size++)
    {
        /*add the string to the list*/
        byte = Byte_Init(*ptr);
        if(!Byte_Add(byte, bytes))
        {
            Log(eError, "failed adding byte to list");
            return false;
        }
    }
    
    /*add null char to the list*/
    byte = Byte_Init(0);
    if(!Byte_Add(byte, bytes))
    {
        Log(eError, "failed adding byte to list");
        return false;
    }
        
    return true;
}

bool StringCommandHandler_IsHandler(const char* command)
{ 
    return DataUtils_IsCommand(command,STRING_COMMAND_STR);
} 

size_t StringCommandHandler_GetSize(const char* line)
{
    const char* params = DataUtils_GetParams(line);
    /*byte for each character plus null char minus "" chars*/
    return String_Len(params) - 2 + 1;
}


size_t MatCommandHandler_CalculateSize(const char* matStr)
{
    char buffer[MAX_MAT_SIZE_STR_LEN];
    char* numberStr = NULL;
    int size = 1;
    if(!matStr)
    {
        Log(eError,PARAM_ERR);
        return 0;
    }
    
    String_Copy(buffer, matStr, MAX_MAT_SIZE_STR_LEN);

    numberStr = String_Split(buffer, MAT_CLOSE);
    do
    {
        if(numberStr[0] != MAT_OPEN)
        {
            Log(eError, "Recieved a illigal mat size format");
            return size;
        }
        if(!String_IsNumber(&numberStr[1]))
        {
            Log(eError, "recieved a non number if mat size declaration : %s",numberStr);
            return 0;
        }

        size *= Convert_StrToDecimal(&numberStr[1]);
    
    }while((numberStr = String_Split(NULL, MAT_CLOSE)));
    
    return size;
}

bool MatCommandHandler_Add(const char* line,List* bytes,List* symbols)
{
    Byte byte;
    const char* param = DataUtils_GetParams(line);
    char paramsBuf[MAX_MAT_PARAM_LEN];
    char* sizeStr = NULL;
    char* valuesStr = NULL;
    char* valueStr = NULL;
    int size = 0;

    if(!line || !bytes)
    {
        Log(eError, PARAM_ERR);
        return 0;
    }

    String_Copy(paramsBuf,param,MAX_MAT_PARAM_LEN);

    valuesStr = String_SplitToTwo(paramsBuf,SPACE_CH);
    sizeStr = paramsBuf;
    if(!valuesStr)
    {
        Log(eError, "did not recieve ligal params in mat allocation : %s",line);
        return false;
    }

    size = MatCommandHandler_CalculateSize(sizeStr);
    if(size == 0)
    {
        Log(eError, "Recieved illigal Mat Size Format");
        return 0;
    }

    valueStr = String_Split(valuesStr,COMMA_STR);
    if(valueStr)
    {
        do
        {
            if(size == 0)
            {
                Log(eError, "To Many Values for mat size");
                return size;
            }

            if(!String_IsNumber(valueStr))
            {
                Log(eError, "recieved non number is mat command : %s",valueStr);
                return false;
            }
            byte = Byte_Init(Convert_StrToDecimal(valueStr));
            if(!Byte_Add(byte,bytes))
            {
                Log(eError, "failed in byte insertion");
                return false;
            }
            size--;
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }

    while(size != 0)
    {
        byte = Byte_Init(0);
        if(!Byte_Add(byte,bytes))
        {
            Log(eError, "failed in byte insertion");
            return false;
        }
        size--;
    }

    return true;
}

bool MatCommandHandler_IsHandler(const char* command)
{
    return DataUtils_IsCommand(command,MAT_COMMAND_STR);
}

size_t MatCommandHandler_GetSize(const char* line)
{
    char buffer[MAX_MAT_PARAM_LEN];
    const char* params = DataUtils_GetParams(line);
    char* endSizeStr = NULL;
    
    if(!params)
    {
        Log(eError, PARAM_ERR);
        return 0;
    }

    endSizeStr = String_FindChar(params,SPACE_CH);
    if(endSizeStr > params)
    {
        String_Copy(buffer,params,(endSizeStr - params));

        return MatCommandHandler_CalculateSize(buffer);
    }
    
    return 0;
}

bool DataCommandHandler_IsHandler(const char* command)
{
    return DataUtils_IsCommand(command,DATA_COMMAND_STR);
}

size_t DataCommandHandler_GetSize(const char* line)
{
    const char* params = DataUtils_GetParams(line);
    char buffer[MAX_MAT_PARAM_LEN];
    char* ptr = NULL;
    size_t size = 0;
    if(!params)
    {
        Log(eError, "Recieved data command with no parameters : %s",params);
        return 0;
    }

    String_Copy(buffer,params,MAX_MAT_PARAM_LEN);

    ptr = String_Split(buffer,COMMA_STR);
    if(!ptr)
    {
        Log(eError, "Recieved data command with no parameters : %s",params);
        return 0;
    }

    do
    {
        size++;            
    }while((ptr = String_Split(NULL,COMMA_STR)));
    
    return size;
}

bool DataCommandHandler_Add(const char* line,List* bytes, List* symbols)
{
    Byte byte;
    const char* params = DataUtils_GetParams(line);
    char buffer[MAX_MAT_PARAM_LEN];
    char* valueStr = NULL;
    int value = 0;
    
    if(!params || !bytes)
    {
        Log(eError, PARAM_ERR);
        return 0;
    }

    String_Copy(buffer,params,MAX_MAT_PARAM_LEN);

    valueStr = String_Split(buffer,COMMA_STR);
    if(valueStr)
    {
        do
        {
            if(!String_IsNumber(valueStr))
            {
                Log(eError, "Recieved a parameter that is not a number in command : %s",valueStr);
                return false;
            }

            value = Convert_StrToDecimal(valueStr);
            byte = Byte_Init(value);
            if(!Byte_Add(byte,bytes))
            {
                Log(eError, "Failed Adding byte to byte list");
                return false;
            }
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }
    
    return true;
}



