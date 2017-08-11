#include "ProgrammeDefines.h"
#include "ComputerConfig.h"

#define PORGRAMME_BUFFER_LENGTH (MEMORY_LEN) // for now each programme has all of the address space 

// a Symbol pointing to a programme memory address
struct Symbol
{
	uint8_t address;
	char Symbol[MAX_COMMAND_LEN]
};

// a table connecting all the Symbols to there addresses
struct SymbolTable
{
	size_t SymbolCount; 		// the current symole count
	Symbol Symbols[MEMORY_LEN] //there could not be more Symboles then memory 
};

struct Segment
{

};


// A programme data structure
struct Programme
{
	SymbolTable SymbolTable;
	Word Buffer[PORGRAMME_BUFFER_LENGTH];
	Segment dataSegment;
	Segment codeSegment;
};




