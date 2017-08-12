#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Symbol.h"

/**
    The Symbol Table Contains all the symbols in an assembly file
*/
typedef struct SymbolTable
{
    size_t count;
    Symbol *symbols;
}SymbolTable;

/*
    Create a symbol table
*/
SymbolTable SymbolTable_Init();


SymbolTable SymbolTable_Copy(SymbolTable* other);

/**
    Adds a symbol to the symbol table
*/
bool SymbolTable_AddSymbol(SymbolTable* table,Symbol* symbol);


void SymbolTable_Print(SymbolTable* table);

/**
    Clean all resources of the Symbol Table
*/
void SymbolTable_Delete(SymbolTable* table);

#endif