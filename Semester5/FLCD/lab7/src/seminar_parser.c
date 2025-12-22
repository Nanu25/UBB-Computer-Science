#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

typedef enum {
    ST_A = 0,
    ST_LPAREN,
    ST_RPAREN,
    ST_PLUS,
    ST_MUL,
    ST_EOF,
    ST_COUNT
} SemTerminal;

typedef enum {
    S_NT = 0,
    A_NT,
    B_NT,
    C_NT,
    D_NT,
    NT_COUNT
} SemNonTerminal;

typedef enum {
    SYM_TERM = 0,
    SYM_NONTERM
} SemSymbolType;

typedef struct {
    SemSymbolType type;
    int value;
} SemSymbol;

typedef struct {
    SemNonTerminal lhs;
    int rhs_len;
    SemSymbol rhs[4];
    const char *text;
} SemProduction;

typedef struct {
    int id;
    SemSymbolType kind;  // SYM_TERM or SYM_NONTERM
    int symbol_id;       // terminal or nonterminal value
    int parent;
    int sibling;
} ParseNode;

typedef struct {
    SemSymbolType type;
    int value;
    int node_id;  // for parse tree tracking
} StackEntry;

typedef struct {
    int *items;
    int count;
    int cap;
} ProductionList;

typedef struct {
    ParseNode *nodes;
    int node_count;
    int node_cap;
} ParseTree;

static SemProduction productions[8];
static int parse_table[NT_COUNT][ST_COUNT];

static SemSymbol make_term(SemTerminal t) {
    SemSymbol s = {SYM_TERM, (int)t};
    return s;
}

static SemSymbol make_nonterm(SemNonTerminal nt) {
    SemSymbol s = {SYM_NONTERM, (int)nt};
    return s;
}

static void init_grammar(void) {
    productions[0] = (SemProduction){S_NT, 2, {make_nonterm(B_NT), make_nonterm(A_NT)}, "S -> B A"};
    productions[1] = (SemProduction){A_NT, 3, {make_term(ST_PLUS), make_nonterm(B_NT), make_nonterm(A_NT)}, "A -> + B A"};
    productions[2] = (SemProduction){A_NT, 0, {0}, "A -> epsilon"};
    productions[3] = (SemProduction){B_NT, 2, {make_nonterm(D_NT), make_nonterm(C_NT)}, "B -> D C"};
    productions[4] = (SemProduction){C_NT, 3, {make_term(ST_MUL), make_nonterm(D_NT), make_nonterm(C_NT)}, "C -> * D C"};
    productions[5] = (SemProduction){C_NT, 0, {0}, "C -> epsilon"};
    productions[6] = (SemProduction){D_NT, 3, {make_term(ST_LPAREN), make_nonterm(S_NT), make_term(ST_RPAREN)}, "D -> ( S )"};
    productions[7] = (SemProduction){D_NT, 1, {make_term(ST_A)}, "D -> a"};

    for (int i = 0; i < NT_COUNT; ++i) {
        for (int j = 0; j < ST_COUNT; ++j) {
            parse_table[i][j] = -1;
        }
    }

    parse_table[S_NT][ST_LPAREN] = 0;
    parse_table[S_NT][ST_A] = 0;

    parse_table[A_NT][ST_PLUS] = 1;
    parse_table[A_NT][ST_RPAREN] = 2;
    parse_table[A_NT][ST_EOF] = 2;

    parse_table[B_NT][ST_LPAREN] = 3;
    parse_table[B_NT][ST_A] = 3;

    parse_table[C_NT][ST_MUL] = 4;
    parse_table[C_NT][ST_PLUS] = 5;
    parse_table[C_NT][ST_RPAREN] = 5;
    parse_table[C_NT][ST_EOF] = 5;

    parse_table[D_NT][ST_LPAREN] = 6;
    parse_table[D_NT][ST_A] = 7;
}

static const char *terminal_name(SemTerminal t) {
    switch (t) {
        case ST_A: return "a";
        case ST_LPAREN: return "(";
        case ST_RPAREN: return ")";
        case ST_PLUS: return "+";
        case ST_MUL: return "*";
        case ST_EOF: return "EOF";
        default: return "?";
    }
}

static const char *nonterminal_name(SemNonTerminal nt) {
    switch (nt) {
        case S_NT: return "S";
        case A_NT: return "A";
        case B_NT: return "B";
        case C_NT: return "C";
        case D_NT: return "D";
        default: return "?";
    }
}

static void push_production(ProductionList *list, int index) {
    if (list->count >= list->cap) {
        int new_cap = list->cap == 0 ? 16 : list->cap * 2;
        int *tmp = (int *)realloc(list->items, (size_t)new_cap * sizeof(int));
        if (!tmp) {
            fprintf(stderr, "Out of memory while storing productions\n");
            exit(EXIT_FAILURE);
        }
        list->items = tmp;
        list->cap = new_cap;
    }
    list->items[list->count++] = index;
}

static SemTerminal token_from_string(const char *tok) {
    if (strcmp(tok, "a") == 0) return ST_A;
    if (strcmp(tok, "(") == 0) return ST_LPAREN;
    if (strcmp(tok, ")") == 0) return ST_RPAREN;
    if (strcmp(tok, "+") == 0) return ST_PLUS;
    if (strcmp(tok, "*") == 0) return ST_MUL;
    if (strcmp(tok, "EOF") == 0 || strcmp(tok, "eof") == 0) return ST_EOF;
    return (SemTerminal)(-1);
}

static int load_tokens(const char *path, SemTerminal **out_tokens, size_t *out_len) {
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Failed to open input token file");
        return 0;
    }
    SemTerminal *buffer = NULL;
    size_t len = 0, cap = 0;
    char tok[32];
    while (fscanf(f, "%31s", tok) == 1) {
        SemTerminal t = token_from_string(tok);
        if ((int)t < 0) {
            fprintf(stderr, "Unknown token %s\n", tok);
            free(buffer);
            fclose(f);
            return 0;
        }
        if (len >= cap) {
            size_t new_cap = cap == 0 ? 32 : cap * 2;
            SemTerminal *tmp = (SemTerminal *)realloc(buffer, new_cap * sizeof(SemTerminal));
            if (!tmp) {
                fprintf(stderr, "Out of memory reading tokens\n");
                free(buffer);
                fclose(f);
                return 0;
            }
            buffer = tmp;
            cap = new_cap;
        }
        buffer[len++] = t;
    }
    fclose(f);
    if (len == 0 || buffer[len - 1] != ST_EOF) {
        if (len >= cap) {
            SemTerminal *tmp = (SemTerminal *)realloc(buffer, (cap + 1) * sizeof(SemTerminal));
            if (!tmp) {
                fprintf(stderr, "Out of memory appending EOF\n");
                free(buffer);
                return 0;
            }
            buffer = tmp;
            cap += 1;
        }
        buffer[len++] = ST_EOF;
    }
    *out_tokens = buffer;
    *out_len = len;
    return 1;
}

static int write_output(const ProductionList *list, const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Failed to open output file");
        return 0;
    }
    for (int i = 0; i < list->count; ++i) {
        fprintf(f, "%s\n", productions[list->items[i]].text);
    }
    fclose(f);
    return 1;
}

static void ensure_tree_capacity(ParseTree *tree) {
    if (tree->node_count >= tree->node_cap) {
        int new_cap = tree->node_cap == 0 ? 32 : tree->node_cap * 2;
        ParseNode *tmp = (ParseNode *)realloc(tree->nodes, (size_t)new_cap * sizeof(ParseNode));
        if (!tmp) {
            fprintf(stderr, "Out of memory for parse tree\n");
            exit(EXIT_FAILURE);
        }
        tree->nodes = tmp;
        tree->node_cap = new_cap;
    }
}

static int add_tree_node(ParseTree *tree, SemSymbolType kind, int symbol_id, int parent) {
    ensure_tree_capacity(tree);
    ParseNode *node = &tree->nodes[tree->node_count];
    node->id = tree->node_count;
    node->kind = kind;
    node->symbol_id = symbol_id;
    node->parent = parent;
    node->sibling = -1;
    return tree->node_count++;
}

static const char *symbol_name(SemSymbolType kind, int symbol_id) {
    if (kind == SYM_TERM) {
        return terminal_name((SemTerminal)symbol_id);
    } else {
        return nonterminal_name((SemNonTerminal)symbol_id);
    }
}

static int write_parse_tree_csv(const ParseTree *tree, const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Failed to open parse tree CSV file");
        return 0;
    }
    fprintf(f, "id,symbol,parent,sibling,kind\n");
    for (int i = 0; i < tree->node_count; ++i) {
        const ParseNode *node = &tree->nodes[i];
        const char *kind_str = (node->kind == SYM_TERM) ? "terminal" : "nonterminal";
        fprintf(f, "%d,%s,%d,%d,%s\n",
                node->id,
                symbol_name(node->kind, node->symbol_id),
                node->parent,
                node->sibling,
                kind_str);
    }
    fclose(f);
    return 1;
}

static int parse(const SemTerminal *tokens, size_t len, ProductionList *out_list, ParseTree *tree) {
    StackEntry stack[64];
    int top = 0;
    
    int root_id = add_tree_node(tree, SYM_NONTERM, S_NT, -1);
    stack[top++] = (StackEntry){SYM_TERM, ST_EOF, -1};
    stack[top++] = (StackEntry){SYM_NONTERM, S_NT, root_id};

    size_t idx = 0;
    SemTerminal lookahead = tokens[idx];
    while (top > 0) {
        StackEntry cur = stack[--top];
        if (cur.type == SYM_TERM) {
            if (cur.value != lookahead) {
                fprintf(stderr, "Expected token %s, got %s\n",
                        terminal_name((SemTerminal)cur.value),
                        terminal_name(lookahead));
                return 0;
            }
            if (lookahead != ST_EOF) {
                lookahead = (++idx < len) ? tokens[idx] : ST_EOF;
            }
        } else {
            int prod_idx = parse_table[cur.value][lookahead];
            if (prod_idx < 0) {
                fprintf(stderr, "No rule for %s with lookahead %s\n",
                        nonterminal_name((SemNonTerminal)cur.value),
                        terminal_name(lookahead));
                return 0;
            }
            const SemProduction *prod = &productions[prod_idx];
            push_production(out_list, prod_idx);
            
            if (prod->rhs_len == 0) {
                continue;
            }
            
            int child_ids[4];
            for (int i = 0; i < prod->rhs_len; ++i) {
                child_ids[i] = add_tree_node(tree, prod->rhs[i].type, prod->rhs[i].value, cur.node_id);
            }
            for (int i = 0; i < prod->rhs_len - 1; ++i) {
                tree->nodes[child_ids[i]].sibling = child_ids[i + 1];
            }
            for (int i = prod->rhs_len - 1; i >= 0; --i) {
                stack[top++] = (StackEntry){prod->rhs[i].type, prod->rhs[i].value, child_ids[i]};
            }
        }
    }
    return 1;
}

static void print_usage(void) {
    printf("Usage: seminar_parser --input <tokens.txt> --output <dir>\n");
    printf("Tokens should be space-separated a, (, ), +, * (EOF will be appended automatically).\n");
}

static int build_path(char *buffer, size_t size, const char *dir, const char *file) {
#ifdef _WIN32
    int written = snprintf(buffer, size, "%s\\%s", dir, file);
#else
    int written = snprintf(buffer, size, "%s/%s", dir, file);
#endif
    return written > 0 && (size_t)written < size;
}

int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *output_dir = "out";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
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

    SemTerminal *tokens = NULL;
    size_t token_len = 0;
    if (!load_tokens(input_path, &tokens, &token_len)) {
        return 1;
    }

    ProductionList list = {0};
    ParseTree tree = {0};
    init_grammar();
    if (!parse(tokens, token_len, &list, &tree)) {
        free(tokens);
        free(list.items);
        free(tree.nodes);
        return 1;
    }

#ifdef _WIN32
    _mkdir(output_dir);
#else
    mkdir(output_dir, 0755);
#endif
    char prod_path[512];
    char tree_path[512];
    if (!build_path(prod_path, sizeof(prod_path), output_dir, "seminar_productions.txt") ||
        !build_path(tree_path, sizeof(tree_path), output_dir, "seminar_parse_tree.csv")) {
        fprintf(stderr, "Failed to build output paths\n");
        free(tokens);
        free(list.items);
        free(tree.nodes);
        return 1;
    }
    if (!write_output(&list, prod_path)) {
        free(tokens);
        free(list.items);
        free(tree.nodes);
        return 1;
    }
    if (!write_parse_tree_csv(&tree, tree_path)) {
        free(tokens);
        free(list.items);
        free(tree.nodes);
        return 1;
    }

    printf("Seminar grammar parsed successfully.\n");
    printf("Productions written to %s\n", prod_path);
    printf("Parse tree table written to %s\n", tree_path);

    free(tokens);
    free(list.items);
    free(tree.nodes);
    return 0;
}


