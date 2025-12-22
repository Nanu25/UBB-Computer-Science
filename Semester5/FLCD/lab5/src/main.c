#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"
#include "tokens.h"

// Flex generated scanner
int yylex(void);
extern FILE *yyin;

// Globals for scanner hooks
FILE *pifFile = NULL;
FILE *errFile = NULL;
SymbolTable *globalST = NULL;

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s <source_file>\n", prog);
}

int main(int argc, char **argv) {
    const char *inputPath = NULL;
    if (argc >= 2) {
        inputPath = argv[1];
    } else {
        inputPath = "geometry2LFTC.txt"; // default provided sample
    }

    yyin = fopen(inputPath, "r");
    if (!yyin) {
        fprintf(stderr, "Cannot open input file: %s\n", inputPath);
        return 1;
    }

    pifFile = fopen("pif.txt", "w");
    errFile = fopen("lexical_errors.txt", "w");
    if (!pifFile || !errFile) {
        fprintf(stderr, "Cannot open output files.\n");
        fclose(yyin);
        if (pifFile) fclose(pifFile);
        if (errFile) fclose(errFile);
        return 1;
    }

    globalST = st_create(211);
    if (!globalST) {
        fprintf(stderr, "Failed to create Symbol Table.\n");
        fclose(yyin);
        fclose(pifFile);
        fclose(errFile);
        return 1;
    }

    // Run lexer
    yylex();

    // Finalize outputs
    fclose(pifFile);
    fclose(errFile);

    // Write ST
    if (!st_write_to_file(globalST, "st.txt")) {
        fprintf(stderr, "Failed to write st.txt\n");
    }

    st_destroy(globalST);
    fclose(yyin);

    printf("Lexical analysis complete. Outputs: pif.txt, st.txt, lexical_errors.txt\n");
    return 0;
}
