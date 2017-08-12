#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdbool.h>


#define ASSEMBLY_END (".as")
#define OBJECT_END (".ob")
#define EXTERN_END (".ext")
#define ENTRY_END (".ent")

/*
	Return whether or not the if an assembly file
	note : for now will return true if the file is with the ending .as or if the file has no ending

    fileName -  a null terminated ascii format array of the filename

    return :true - the file given is a assembly file
            false - the file does not meat the requirments

*/
bool Assembler_IsAssemblyFile(const char* fileName);

/*
    Run the Assembler Process on the file this will create all the needed files and report all errors to
    the stdout

    return  :   true-successfully assembled file
                false-somthing went wrong
*/
bool Assembler_AssembleFile(char* AssemblerFile);

#endif