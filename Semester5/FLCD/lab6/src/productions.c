#include "productions.h"

char productions_buffer[10000] = {0};
int productions_count = 0;

void init_productions(void) {
    productions_buffer[0] = '\0';
    productions_count = 0;
}

void add_production(const char* prod) {
    if (!prod) return;
    
    size_t current_len = strlen(productions_buffer);
    size_t prod_len = strlen(prod);
    
    // Check if we have space (leave room for newline and null terminator)
    if (current_len + prod_len + 2 < sizeof(productions_buffer)) {
        if (current_len > 0) {
            strcat(productions_buffer, "\n");
            current_len++;
        }
        strcat(productions_buffer, prod);
        productions_count++;
    }
}

void write_productions_to_file(const char* filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error: Cannot open file %s for writing\n", filename);
        return;
    }
    
    fprintf(f, "%s\n", productions_buffer);
    fclose(f);
}

