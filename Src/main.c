#include "OSDefines.h"
#include <stdio.h>

#include "Assembler.h"
#include "Log.h"
#include "Memory.h"
#include "File.h"

#define MIN_ARG_COUNT (2)


/*
	Prints to stdout a helful help menu with the explanation on how to use the programme
*/
void PrintHelpMenu()
{
	printf("Usage: ./assembler fileName fileName...\n");
}


/*
This is the main entry point of the programe
*/
int main(int argc, char* argv[])
{
	char* files[MAX_FILE_NAME];
	int i = 0;
	int fileCount = 0;

	if(argc < MIN_ARG_COUNT)
	{
		PrintHelpMenu();
	}
	
	/*	Create an array of all the ligal files*/
	for(i=1; i<argc; i++)
	{

		if(Assembler_IsAssemblyFile(argv[i]))
		{
			/* Allocate a new array for the file name*/
			files[fileCount] = Memory_Allocate(NAME_MAX * sizeof(char));
			if(!files[fileCount])
			{
				Log(eError,MEMORY_ERR);
				return 1;
			}

			if(File_CleanName(argv[i], files[fileCount], NAME_MAX))
			{
				fileCount++;	
			}
			else
			{
				Log(eError, "Failed Extracting File Name"); 	
			}	
		}
		else
		{
			Log(eError, "File Provided Isn't an assembly file");
		}
	}

	for(i=0; i< fileCount; i++)
	{
		Assembler_AssembleFile(files[i]);
	}

	for(i=0; i < fileCount; i++)
	{
		Memory_Delete(files[i]);
	}

    return 0;
}




