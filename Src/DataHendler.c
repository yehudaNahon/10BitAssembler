
#include "DataHandler.h"


size_t DataHandler_StringHandler(char* params, void* table)
{
    return 1;
}

size_t DataHandler_MatHandler(char* params, void* table)
{
    return 1;
}

size_t DataHandler_DataHandler(char* params, void* table)
{
    return 1;
}


#define DATA_NUM_OF_ELEM (3)
Handler dataHandlers[] = {
    {".data", &DataHandler_DataHandler},
    {".mat", &DataHandler_MatHandler},
    {".string", &DataHandler_StringHandler}
};


bool DataHandler_IsLine(char* command)
{
    return Handler_IsInList(command, dataHandlers, DATA_NUM_OF_ELEM);
}

size_t DataHandler_AddLine(char* command,char* params, ByteTable* table)
{
    return Handler_AddLine(command, table, dataHandlers, DATA_NUM_OF_ELEM);
}
