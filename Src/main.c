#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <malloc.h>

#include "Assembler.h"
#include "FileUtils.h"
#include "Log.h"

#define MIN_ARG_COUNT (2)

#define MEMORY_ERR ("Failed Locating Memory")

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
	char* files[NAME_MAX];
	char temp[NAME_MAX];
	int i = 0;
	int fileCount = 0;

	if(argc < MIN_ARG_COUNT)
	{
		PrintHelpMenu();
	}
	
	/*	Create an array of all the ligal files*/
	for(i=1; i<argc; i++)
	{

		if(IsAssemblyFile(argv[i]))
		{
			/* Allocate a new array for the file name*/
			files[fileCount] = malloc(NAME_MAX * sizeof(char));
			if(!files[fileCount])
			{
				Log(eError,MEMORY_ERR);
				return 1;
			}

			if(CleanFileName(argv[i], files[fileCount], NAME_MAX))
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
		CreateFileName(files[i],ASSEMBLY_END,temp,NAME_MAX);
		AssembleFile(temp);
	}

	for(i=0; i < fileCount; i++)
	{
		free(files[i]);
	}

    return 0;
}




