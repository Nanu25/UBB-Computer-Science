#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTIONS 1000
#define MAX_PROD_LENGTH 200

// Buffer to store all productions
extern char productions_buffer[10000];
extern int productions_count;

// Function to add a production rule
void add_production(const char* prod);

// Function to write productions to file
void write_productions_to_file(const char* filename);

// Function to initialize productions tracking
void init_productions(void);

#endif // PRODUCTIONS_H

