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

/*copy the command to the buffer*/
bool DataUtils_GetCommand(const char* line, char* buffer,size_t len)
{
    String_Copy(buffer,line,len);
    return String_SplitToTwo(buffer,SPACE_CH) != NULL;
}

/*return the parameters*/
char* DataUtils_GetParams(const char* line)
{
    return String_FindChar(line,SPACE_CH) + 1;
}

/*checks if the commandStr matches to command*/
bool DataUtils_IsCommand(const char* commandStr,const char* command)
{
    if(!commandStr || !command)
    {
        return false;
    }

    return String_Compare(commandStr,command,MIN(String_Len(command),String_Len(commandStr))) == 0;
}

/*adds string command bytes to the byte list*/
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

/*check if the command is a string command*/
bool StringCommandHandler_IsHandler(const char* command)
{ 
    return DataUtils_IsCommand(command,STRING_COMMAND_STR);
} 

/*return the size of the command in bytes*/
size_t StringCommandHandler_GetSize(const char* line)
{
    const char* params = DataUtils_GetParams(line);
    /*byte for each character plus null char minus "" chars*/
    return String_Len(params) - 2 + 1;
}

/*calculates the number of bytes to write ti the list table for the mat command*/
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
    
    /*copy the mat to the buffer*/
    String_Copy(buffer, matStr, MAX_MAT_SIZE_STR_LEN);

    /*split by closing char*/
    numberStr = String_Split(buffer, MAT_CLOSE);
    do
    {
        /*check the user proided a mat open char*/
        if(numberStr[0] != MAT_OPEN)
        {
            Log(eError, "Recieved a illigal mat size format");
            return size;
        }
        /*check the param provided is a number*/
        if(!String_IsNumber(&numberStr[1]))
        {
            Log(eError, "recieved a non number if mat size declaration : %s",numberStr);
            return 0;
        }
        /*convert to number str*/
        size *= Convert_StrToDecimal(&numberStr[1]);
    
    }while((numberStr = String_Split(NULL, MAT_CLOSE)));
    
    return size;
}

/*add mat command byte to the byte list*/
bool MatCommandHandler_Add(const char* line,List* bytes,List* symbols)
{
    Byte byte;
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
    
    /*locate the params and copy them*/
    const char* param = DataUtils_GetParams(line);
    String_Copy(paramsBuf,param,MAX_MAT_PARAM_LEN);

    /*split the parameters by space*/
    valuesStr = String_SplitToTwo(paramsBuf,SPACE_CH);
    sizeStr = paramsBuf;
    if(!valuesStr)
    {
        Log(eError, "did not recieve ligal params in mat allocation : %s",line);
        return false;
    }

    /*calculate the mat size*/
    size = MatCommandHandler_CalculateSize(sizeStr);
    if(size == 0)
    {
        Log(eError, "Recieved illigal Mat Size Format");
        return 0;
    }

    /*split the initial values using a comma*/
    valueStr = String_Split(valuesStr,COMMA_STR);
    if(valueStr)
    {
        do
        {
            /*check there bytes left*/
            if(size == 0)
            {
                Log(eError, "To Many Values for mat size");
                return size;
            }

            /*check the param is a number*/
            if(!String_IsNumber(valueStr))
            {
                Log(eError, "recieved non number is mat command : %s",valueStr);
                return false;
            }

            /*convert to a number*/
            byte = Byte_Init(Convert_StrToDecimal(valueStr));
            if(!Byte_Add(byte,bytes))
            {
                Log(eError, "failed in byte insertion");
                return false;
            }
            size--;
            
        }while((valueStr = String_Split(NULL,COMMA_STR)));
    }

    /*fill the rest of the bytes with 0*/
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

/*returns the number of bytes the mat takes*/
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

/*returns the size in bytes of the data command*/
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

    /*copy to buffer*/
    String_Copy(buffer,params,MAX_MAT_PARAM_LEN);

    /*split parameters*/
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

/*add data command bytes to byte list*/
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

    /*copy to buffer<*/
    String_Copy(buffer,params,MAX_MAT_PARAM_LEN);

    /*split to parameters*/
    valueStr = String_Split(buffer,COMMA_STR);
    if(valueStr)
    {
        do
        {
            /*check the param is a number*/
            if(!String_IsNumber(valueStr))
            {
                Log(eError, "Recieved a parameter that is not a number in command : %s",valueStr);
                return false;
            }

            /*convert into a number*/
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



