# Source, Executable, Includes, Library Defines
#----------------------libs--------------------


#conteiner
CONTAINER_H = Container.h

HANDLERS_H = Handlers.h Handler.h
HANDLERS_C = Handlers.c

#assembler
ASSEMBLER_H = Assembler.h AssemblerInternals.h
ASSEMBLER_C = Assembler.c

#assembly
ASSEMBLY_H = Assembly.h
ASSEMBLY_C = Assembly.c

#file
FILE_H = File.h
FILE_C = File.c

#Symbol table
SYMBOL_TABLE_H = SymbolTable.h
SYMBOL_TABLE_C = SymbolTable.c

#symbol
SYMBOL_H = Symbol.h SymbolInternals.h
SYMBOL_C = Symbol.c

#log
LOG_H = Log.h
LOG_C = Log.c

#memory
MEMORY_H = Memory.h
MEMORY_C = Memory.c

#string
STRING_H = String.h
STRING_C = String.c

#queue
QUEUE_H = Queue.h 
QUEUE_C = Queue.c

#LinkedList
LINKED_LIST_H = LinkedList.h 
LINKED_LIST_C = LinkedList.c

#macros
MACROS = GeneralMacros.h


INCL   = $(CONTAINER_H) $(ASSEMBLER_H) $(FILE_H) $(SYMBOL_TABLE_H) $(SYMBOL_H) $(LOG_H) $(MEMORY_H) $(MACROS) $(STRING_H) $(ASSEMBLY_H) $(QUEUE_H) $(LINKED_LIST_H) $(HANDLERS_H) $(HANDLER_H)
SRC    = main.c $(ASSEMBLER_C) $(FILE_C) $(SYMBOL_TABLE_C) $(SYMBOL_C) $(LOG_C) $(MEMORY_C) $(STRING_C) $(ASSEMBLY_C) $(QUEUE_C) $(LINKED_LIST_C) $(HANDLER_C) $(HANDLERS_C) 
OBJ    = $(SRC:.c=.o)
LIBS   = 
EXE    = Assembler

# Compiler, Linker Defines
CC      = /usr/bin/gcc
CFLAGS  = -ansi -pedantic -Wall -O2
LIBPATH = -L.
LDFLAGS = -o $(EXE) $(LIBPATH) $(LIBS)
CFDEBUG = -ansi -pedantic -Wall -g -DDEBUG $(LDFLAGS)
RM      = /bin/rm -f

# Compile and Assemble C Source Files into Object Files
%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Create a gdb/dbx Capable Executable with DEBUG flags turned on
debug:
	$(CC) $(CFDEBUG) $(SRC)

# Clean Up Objects, Exectuables, Dumps out of source directory
clean:
	$(RM) $(OBJ) $(EXE) core a.out