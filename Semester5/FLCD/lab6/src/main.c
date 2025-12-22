#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "productions.h"

extern FILE *yyin;
extern int yyparse(void);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    // Initialize productions tracking
    init_productions();

    // Set input file for lexer
    yyin = input;

    // Parse the input
    int result = yyparse();

    fclose(input);

    if (result == 0) {
        printf("Parsing successful!\n");
        // Write productions to file
        write_productions_to_file("productions.txt");
        printf("Productions written to productions.txt\n");
    } else {
        fprintf(stderr, "Parsing failed!\n");
        return 1;
    }

    return 0;
}

