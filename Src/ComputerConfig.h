#ifndef COMPUTER_CONFIG_H
#define COMPUTER_CONFIG_H 

#include <stdint.h>

/*************************************************
			SYSTEM CONFIGUTRATION

this is a file containing the configuration of the 
for mentioned system with its registers and memory
****************************************************/

//	Number of general registers
#define GENERAL_REGISRTERS_LEN (8)

// The length of the memory in the computer
#define MEMORY_LEN (255)

// Number of bits in a word
#define WORD_LENGTH (10)


// A single word in the computer 
struct Word
{
    uint16_t data : WORD_LENGTH;
};

// A register
typedef Word register_t;


struct  Stack
{
	Word* begin;
	Word* end;
	Word* sp;
};

struct Cpu
{
	register_t generalRegisters[GENERAL_REGISRTERS_LEN];	// the cpu's general registeres
    register_t psw;											// the cpu's flag register
    register_t pc; 											// the programme pointer
    Stack stack;											// the stack pointer
};


// A look up table linking the registers value to there string 
// representation 
char* GeneralRegistersLookUpTable[GENERAL_REGISRTERS_LEN] = 
{
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7",
};


// A representation of a computer system
struct Computer
{
    Cpu cpu;
    Word memory[MEMORY_LEN];
};



#endif