# Declaration of variables
CC = gcc
CC_FLAGS = -Wall -ansi -pedantic
 
# File names
EXEC = Assembler
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS) ; $(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp ; $(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean: ;rm -f $(EXEC) $(OBJECTS) *.env *.ext