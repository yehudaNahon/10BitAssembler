#include <stdbool.h>
#include "ProgrammeDefines.h"

/****************************************************

				PROGRAMME API
this is the programme library api all the internal methodes 
are described in the header file "ProgrammeInternals.h"
*****************************************************/


/*
	Assemble a programme
	
	lines - 		an array of ascii string all terminated by a NULL character 
	length-			the number of lines in the array
	buffer-			an array of bytes to write the programme to
	bufferLength- 	the buffer length in bytes

*/
bool AssembleProgramme(const char* lines[MAX_COMMAND_LEN], size_t length, uint8_t *o_buffer, size_t bufferLength);
