#include "ProgrammeDefines.h"

/**
								DEAR READER
	This is private implementation of the progrmme Library this file containes all the methodes 
	declaration and documantation
*/



/*
	Create a new empty Programme
	
	return: return a new Programme object
*/
Programme InitProgramme();


/*
	Create the programmes symbol table all the labels will be marked with the lines indexes

	note : 	In case of an error or warning the message will be printed to stdout
	
	programme -	the programmes instence
	lines - 	a 2 demential array on chars containing all the code lines in the programme 
	len   - 	the number of lines in the programme 

	return: true - success
			false- falied
*/
bool CreateSymbolTable(Programme &programme, char* lines[MAX_COMMAND_LEN], size_t len);

/*
	Assemble the programme to the programmes memory

	note :	In case of an error or warning the message will be printed to stdout

	programme -	the programmes instence
	lines - 	a 2 demential array on chars containing all the code lines in the programme 
	len   - 	the number of lines in the programme 

	return: true - success
			false- falied
*/
bool AssembleProgramme(Programme &programme, char* lines[MAX_COMMAND_LEN], size_t len);


/**
	Return the programmes data after assembly
*/
bool GetAssembledProgramme(Programme &programme, Word o_buffer[], size_t len);


/*
	Free the given programmes dynamicly allocated memory

	return :	true - 	success
				false - falied
*/
bool DeleteProgramme(Programme &programme);


