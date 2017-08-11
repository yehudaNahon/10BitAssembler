#include <stdbool.h>


/*
	Return whether or not the if an assembly file
	note : for now will return true if the file is with the ending .as or if the file has no ending

    fileName -  a null terminated ascii format array of the filename

    return :true - the file given is a assembly file
            false - the file does not meat the requirments

*/
bool IsAssemblyFile(const char* fileName);