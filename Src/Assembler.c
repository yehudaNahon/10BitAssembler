#include "Assembler.h"
#include "AssemblerInternals.h"
#include "Assembly.h"
#include "Log.h"
#include "File.h"
#include "String.h"
#include <stdint.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "Queue.h"
#include "Memory.h"
#include "LinkedList.h"


#define LABEL_INDICATOR (':')
#define LABEL_SPLITER (" :")
#define LIGAL_LABEL_CH LETTERS_CH UPPER_CASE_CH NUMBERS_CH


bool Assembler_IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = File_FindDot(fileName);
	
	return ptr == NULL || String_Compare(ptr,ASSEMBLY_END) == 0;
}


/*
    return whether or not the line
*/
bool Assembler_IsCodeLine(char* line)
{
    /* for now will only check that its not a comment*/
    if(String_FindChar(line,';'))
    {
        return false;
    }

    return true;
}


void Assembler_CreateCommand(char* line, size_t index,void* ptr)
{

}

void Assembler_AddToLinkedList(void* line, size_t* len, void* context)
{
    LinkedList* list = (LinkedList*)context;
    if(list)
    {
        LinkedList_Add(list, line, *len);
    }

}


/*
    print the line given to stdout
*/
void Assembler_PrintLine(void* line, size_t* len, void* context)
{
    String_SimplfyLine(line);
    printf("%s\n",(char*)line);
}

bool Assembler_AssembleFile(char* asmFile)
{
    /*Assembly assembly = Assembly_Init(asmFile);*/

    LinkedList list = LinkedList_Init();

    /*open the file*/
    FILE* file = File_Open(asmFile, "r");

    if(!file)
    {
        Log(eError, "Could not open file");
        return false;
    }

    
    /* create symbol table*/
    File_ForEach(file, &Assembler_AddToLinkedList, &list);
    
    LinkedList_ForEach(&list,&Assembler_PrintLine,&list);

    LinkedList_Delete(&list,NULL,NULL);

    /*close the file*/
    if(!File_Close(file))
    {
        Log(eError, "Could not close file");
        return false;
    }

    return true;
}







