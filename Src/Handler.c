#include "Handler.h"
#include "String.h"

bool Handler_IsInList(char* line,Handler handlers[], size_t numOfElements)
{
    int i=0;
    for(i=0;i< numOfElements ; i++)
    {
        /*return true only if the strings are the same from the start*/
        if(!String_Compare(line, handlers[i].command, String_Len(handlers[i].command)))
        {
            return true;
        }
    } 

    return false;
}

bool Handler_AddLine(char* line, LinkedList* list, Handler handlers[], size_t numOfElements)
{
    int i=0;

    for(i=0;i< numOfElements ; i++)
    {        
        /*return true only if the strings are the same from the start*/
        if(String_Compare(line, handlers[i].command, String_Len(handlers[i].command)) == 0)
        {
            return handlers[i].act(line,NULL);
        }
    } 
    return 0;
}
