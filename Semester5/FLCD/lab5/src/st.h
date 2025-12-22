// Symbol Table implemented as a hash table with separate chaining
// Provides deterministic position reporting: (bucketIndex, chainIndex)

#ifndef ST_H
#define ST_H

#include <stdbool.h>

typedef struct STEntry {
    char *key;               // identifier or constant lexeme
    int bucketIndex;         // for reporting consistency
    int chainIndex;          // position inside the bucket chain
    struct STEntry *next;
} STEntry;

typedef struct SymbolTable {
    STEntry **buckets;
    int capacity;            // number of buckets
    int size;                // number of elements
} SymbolTable;

// Create a symbol table with a given number of buckets
SymbolTable *st_create(int capacity);

// Free all resources
void st_destroy(SymbolTable *st);

// Insert key if absent; returns pointer to entry (existing or newly inserted)
STEntry *st_insert(SymbolTable *st, const char *key);

// Lookup key; returns pointer to entry or NULL
STEntry *st_lookup(SymbolTable *st, const char *key);

// Write a textual representation of the ST to a file path
bool st_write_to_file(SymbolTable *st, const char *filepath);

#endif // ST_H


