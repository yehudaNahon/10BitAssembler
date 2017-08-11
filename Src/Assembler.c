#include "Assembler.h"
#include "FileUtils.h"
#include <string.h>


#define ASSEMBLY_END (".as")
#define OBJECT_END (".ob")
#define EXTERN_END (".ext")
#define ENTRY_END (".ent")

bool IsAssemblyFile(const char* fileName)
{
	char* ptr = NULL;

	ptr = FindTypeSplitCharacter(fileName);
	
	return ptr == NULL || strcmp(ptr,ASSEMBLY_END) == 0;
}