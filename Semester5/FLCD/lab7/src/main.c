#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ll1_parser.h"

static void print_usage(void) {
    printf("Usage:\n");
    printf("  ll1_parser --input <path> [--mode pif|tokens] [--output <dir>]\n");
    printf("\n");
    printf("Modes:\n");
    printf("  pif    - read tokens from a Program Internal Form file (default)\n");
    printf("  tokens - read whitespace separated token names (identifier, int, +, ...)\n");
}

static int build_output_path(char *buffer, size_t size, const char *dir, const char *file) {
    if (!buffer || !dir || !file) {
        return 0;
    }
#ifdef _WIN32
    int written = snprintf(buffer, size, "%s\\%s", dir, file);
#else
    int written = snprintf(buffer, size, "%s/%s", dir, file);
#endif
    return written > 0 && (size_t)written < size;
}

int main(int argc, char **argv) {
    const char *mode = "pif";
    const char *input_path = NULL;
    const char *output_dir = "out";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
            mode = argv[++i];
        } else if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            input_path = argv[++i];
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            output_dir = argv[++i];
        } else {
            print_usage();
            return 1;
        }
    }

    if (!input_path) {
        print_usage();
        return 1;
    }

    Terminal *tokens = NULL;
    size_t token_count = 0;
    char load_error[256] = {0};

    if (strcmp(mode, "pif") == 0) {
        if (!load_tokens_from_pif(input_path, &tokens, &token_count, load_error, sizeof(load_error))) {
            fprintf(stderr, "Failed to load PIF: %s\n", load_error[0] ? load_error : "unknown error");
            return 1;
        }
    } else if (strcmp(mode, "tokens") == 0) {
        if (!load_tokens_from_stream(input_path, &tokens, &token_count, load_error, sizeof(load_error))) {
            fprintf(stderr, "Failed to load token stream: %s\n", load_error[0] ? load_error : "unknown error");
            return 1;
        }
    } else {
        fprintf(stderr, "Unknown mode %s\n", mode);
        print_usage();
        return 1;
    }

    ParseResult result;
    char parse_error[256] = {0};
    if (!parse_tokens(tokens, token_count, &result, parse_error, sizeof(parse_error))) {
        fprintf(stderr, "Parsing failed: %s\n", parse_error[0] ? parse_error : "unknown error");
        free(tokens);
        return 1;
    }
    free(tokens);

    if (!ensure_directory(output_dir)) {
        fprintf(stderr, "Failed to ensure output directory %s\n", output_dir);
        free_parse_result(&result);
        return 1;
    }

    char productions_path[512];
    char tree_path[512];
    if (!build_output_path(productions_path, sizeof(productions_path), output_dir, "productions.txt") ||
        !build_output_path(tree_path, sizeof(tree_path), output_dir, "parse_tree.csv")) {
        fprintf(stderr, "Failed to build output paths\n");
        free_parse_result(&result);
        return 1;
    }

    if (!write_productions_file(&result, productions_path)) {
        fprintf(stderr, "Failed to write productions file\n");
        free_parse_result(&result);
        return 1;
    }
    if (!write_parse_tree_table_file(&result, tree_path)) {
        fprintf(stderr, "Failed to write parse tree table\n");
        free_parse_result(&result);
        return 1;
    }

    printf("Parsing completed.\n");
    printf("Productions: %s\n", productions_path);
    printf("Parse tree table: %s\n", tree_path);

    free_parse_result(&result);
    return 0;
}


