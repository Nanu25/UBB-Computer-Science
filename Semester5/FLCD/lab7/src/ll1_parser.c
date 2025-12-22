#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

#include "../include/ll1_parser.h"
#include "../../include/tokens.h"

typedef enum {
    SYMBOL_TERMINAL = 0,
    SYMBOL_NONTERMINAL
} SymbolType;

typedef struct {
    SymbolType type;
    int value;
} Symbol;

typedef struct {
    NonTerminal lhs;
    int rhs_len;
    Symbol rhs[8];
    const char *text;
} Production;

typedef struct {
    SymbolType type;
    int value;
    int node_id;
} StackEntry;

static Production productions[64];
static int production_count = 0;
static int parse_table[NT_COUNT][T_COUNT];
static int grammar_ready = 0;

static Symbol make_terminal(Terminal t) {
    Symbol s = {SYMBOL_TERMINAL, (int)t};
    return s;
}

static Symbol make_nonterminal(NonTerminal nt) {
    Symbol s = {SYMBOL_NONTERMINAL, (int)nt};
    return s;
}

static void add_production(NonTerminal lhs, const Symbol *rhs, int rhs_len, const char *text) {
    if (production_count >= (int)(sizeof(productions) / sizeof(productions[0]))) {
        fprintf(stderr, "Internal error: too many productions\n");
        exit(EXIT_FAILURE);
    }
    Production *prod = &productions[production_count++];
    prod->lhs = lhs;
    prod->rhs_len = rhs_len;
    for (int i = 0; i < rhs_len; ++i) {
        prod->rhs[i] = rhs[i];
    }
    prod->text = text;
}

static void set_table_entry(NonTerminal nt, Terminal t, int production_index) {
    if (parse_table[nt][t] != -1 && parse_table[nt][t] != production_index) {
        fprintf(stderr, "LL(1) conflict at (%s, %s)\n", nonterminal_name(nt), terminal_name(t));
        exit(EXIT_FAILURE);
    }
    parse_table[nt][t] = production_index;
}

static void init_parse_table(void) {
    for (int i = 0; i < NT_COUNT; ++i) {
        for (int j = 0; j < T_COUNT; ++j) {
            parse_table[i][j] = -1;
        }
    }
}

static void build_grammar(void) {
    if (grammar_ready) {
        return;
    }
    init_parse_table();
    production_count = 0;

    // Helper macros for brevity
    #define TT(x) make_terminal(x)
    #define NT(x) make_nonterminal(x)

    add_production(NT_PROGRAM, (Symbol[]){NT(NT_STATEMENT_LIST)}, 1, "program -> statement_list");
    add_production(NT_STATEMENT_LIST, (Symbol[]){NT(NT_STATEMENT), NT(NT_STATEMENT_LIST_TAIL)}, 2, "statement_list -> statement statement_list_tail");
    add_production(NT_STATEMENT_LIST_TAIL, (Symbol[]){NT(NT_STATEMENT), NT(NT_STATEMENT_LIST_TAIL)}, 2, "statement_list_tail -> statement statement_list_tail");
    add_production(NT_STATEMENT_LIST_TAIL, NULL, 0, "statement_list_tail -> epsilon");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_DECLARATION_STATEMENT)}, 1, "statement -> declaration_statement");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_ASSIGNMENT_STATEMENT)}, 1, "statement -> assignment_statement");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_IF_STATEMENT)}, 1, "statement -> if_statement");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_WHILE_STATEMENT)}, 1, "statement -> while_statement");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_IO_STATEMENT)}, 1, "statement -> io_statement");
    add_production(NT_STATEMENT, (Symbol[]){NT(NT_GEOMETRY_STATEMENT)}, 1, "statement -> geometry_statement");
    add_production(NT_IF_STATEMENT, (Symbol[]){TT(T_IF), NT(NT_CONDITION), NT(NT_STATEMENT), NT(NT_IF_STATEMENT_TAIL)}, 4, "if_statement -> if condition statement if_statement_tail");
    add_production(NT_IF_STATEMENT_TAIL, (Symbol[]){TT(T_ELSE), NT(NT_STATEMENT)}, 2, "if_statement_tail -> else statement");
    add_production(NT_IF_STATEMENT_TAIL, NULL, 0, "if_statement_tail -> epsilon");
    add_production(NT_WHILE_STATEMENT, (Symbol[]){TT(T_WHILE), NT(NT_CONDITION), NT(NT_STATEMENT)}, 3, "while_statement -> while condition statement");
    add_production(NT_DECLARATION_STATEMENT, (Symbol[]){NT(NT_TYPE), TT(T_IDENTIFIER), NT(NT_DECLARATION_TAIL)}, 3, "declaration_statement -> type identifier declaration_tail");
    add_production(NT_DECLARATION_TAIL, (Symbol[]){TT(T_ASSIGN), NT(NT_EXPRESSION), TT(T_SEMI)}, 3, "declaration_tail -> = expression ;");
    add_production(NT_DECLARATION_TAIL, (Symbol[]){TT(T_SEMI)}, 1, "declaration_tail -> ;");
    add_production(NT_ASSIGNMENT_STATEMENT, (Symbol[]){TT(T_IDENTIFIER), TT(T_ASSIGN), NT(NT_EXPRESSION), TT(T_SEMI)}, 4, "assignment_statement -> identifier = expression ;");
    add_production(NT_IO_STATEMENT, (Symbol[]){TT(T_WRITE), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_RPAREN), TT(T_SEMI)}, 5, "io_statement -> write ( expression ) ;");
    add_production(NT_IO_STATEMENT, (Symbol[]){TT(T_READ), TT(T_LPAREN), TT(T_IDENTIFIER), TT(T_RPAREN), TT(T_SEMI)}, 5, "io_statement -> read ( identifier ) ;");
    add_production(NT_GEOMETRY_STATEMENT, (Symbol[]){TT(T_AREA_TRIANGLE), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_COMMA), NT(NT_EXPRESSION), TT(T_RPAREN), TT(T_SEMI)}, 7, "geometry_statement -> area_triangle ( expression , expression ) ;");
    add_production(NT_GEOMETRY_STATEMENT, (Symbol[]){TT(T_PYTHAGORAS), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_COMMA), NT(NT_EXPRESSION), TT(T_RPAREN), TT(T_SEMI)}, 7, "geometry_statement -> pythagoras ( expression , expression ) ;");
    add_production(NT_TYPE, (Symbol[]){TT(T_INT)}, 1, "type -> int");
    add_production(NT_TYPE, (Symbol[]){TT(T_FLOAT)}, 1, "type -> float");
    add_production(NT_TYPE, (Symbol[]){TT(T_CHAR)}, 1, "type -> char");
    add_production(NT_TYPE, (Symbol[]){TT(T_STRING)}, 1, "type -> string");
    add_production(NT_CONDITION, (Symbol[]){NT(NT_EXPRESSION), NT(NT_REL_OP), NT(NT_EXPRESSION)}, 3, "condition -> expression relational_operator expression");
    add_production(NT_REL_OP, (Symbol[]){TT(T_EQ)}, 1, "relational_operator -> ==");
    add_production(NT_REL_OP, (Symbol[]){TT(T_NEQ)}, 1, "relational_operator -> !=");
    add_production(NT_REL_OP, (Symbol[]){TT(T_LT)}, 1, "relational_operator -> <");
    add_production(NT_REL_OP, (Symbol[]){TT(T_GT)}, 1, "relational_operator -> >");
    add_production(NT_REL_OP, (Symbol[]){TT(T_LE)}, 1, "relational_operator -> <=");
    add_production(NT_REL_OP, (Symbol[]){TT(T_GE)}, 1, "relational_operator -> >=");
    add_production(NT_EXPRESSION, (Symbol[]){NT(NT_TERM), NT(NT_EXPRESSION_TAIL)}, 2, "expression -> term expression_tail");
    add_production(NT_EXPRESSION_TAIL, (Symbol[]){TT(T_PLUS), NT(NT_TERM), NT(NT_EXPRESSION_TAIL)}, 3, "expression_tail -> + term expression_tail");
    add_production(NT_EXPRESSION_TAIL, (Symbol[]){TT(T_MINUS), NT(NT_TERM), NT(NT_EXPRESSION_TAIL)}, 3, "expression_tail -> - term expression_tail");
    add_production(NT_EXPRESSION_TAIL, NULL, 0, "expression_tail -> epsilon");
    add_production(NT_TERM, (Symbol[]){NT(NT_FACTOR), NT(NT_TERM_TAIL)}, 2, "term -> factor term_tail");
    add_production(NT_TERM_TAIL, (Symbol[]){TT(T_MUL), NT(NT_FACTOR), NT(NT_TERM_TAIL)}, 3, "term_tail -> * factor term_tail");
    add_production(NT_TERM_TAIL, (Symbol[]){TT(T_DIV), NT(NT_FACTOR), NT(NT_TERM_TAIL)}, 3, "term_tail -> / factor term_tail");
    add_production(NT_TERM_TAIL, (Symbol[]){TT(T_MOD), NT(NT_FACTOR), NT(NT_TERM_TAIL)}, 3, "term_tail -> % factor term_tail");
    add_production(NT_TERM_TAIL, NULL, 0, "term_tail -> epsilon");
    add_production(NT_FACTOR, (Symbol[]){TT(T_IDENTIFIER)}, 1, "factor -> identifier");
    add_production(NT_FACTOR, (Symbol[]){TT(T_INT_CONST)}, 1, "factor -> int_const");
    add_production(NT_FACTOR, (Symbol[]){TT(T_FLOAT_CONST)}, 1, "factor -> float_const");
    add_production(NT_FACTOR, (Symbol[]){TT(T_CHAR_CONST)}, 1, "factor -> char_const");
    add_production(NT_FACTOR, (Symbol[]){TT(T_STRING_CONST)}, 1, "factor -> string_const");
    add_production(NT_FACTOR, (Symbol[]){TT(T_SQRT), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_RPAREN)}, 4, "factor -> sqrt ( expression )");
    add_production(NT_FACTOR, (Symbol[]){TT(T_AREA_TRIANGLE), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_COMMA), NT(NT_EXPRESSION), TT(T_RPAREN)}, 6, "factor -> area_triangle ( expression , expression )");
    add_production(NT_FACTOR, (Symbol[]){TT(T_PYTHAGORAS), TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_COMMA), NT(NT_EXPRESSION), TT(T_RPAREN)}, 6, "factor -> pythagoras ( expression , expression )");
    add_production(NT_FACTOR, (Symbol[]){TT(T_LPAREN), NT(NT_EXPRESSION), TT(T_RPAREN)}, 3, "factor -> ( expression )");
    add_production(NT_FACTOR, (Symbol[]){TT(T_MINUS), NT(NT_FACTOR)}, 2, "factor -> - factor");

    #undef TT
    #undef NT

    // Build LL(1) parse table by hand
    // Helper arrays to reduce repetition
    Terminal statement_starters[] = {
        T_INT, T_FLOAT, T_CHAR, T_STRING,
        T_IDENTIFIER, T_IF, T_WHILE,
        T_WRITE, T_READ, T_AREA_TRIANGLE, T_PYTHAGORAS
    };
    int statement_starters_count = (int)(sizeof(statement_starters) / sizeof(statement_starters[0]));

    // program
    for (int i = 0; i < statement_starters_count; ++i) {
        set_table_entry(NT_PROGRAM, statement_starters[i], 0);
        set_table_entry(NT_STATEMENT_LIST, statement_starters[i], 1);
        set_table_entry(NT_STATEMENT_LIST_TAIL, statement_starters[i], 2);
    }
    set_table_entry(NT_STATEMENT_LIST_TAIL, T_EOF, 3);

    // statement productions (indices 4-9)
    Terminal decl_tokens[] = {T_INT, T_FLOAT, T_CHAR, T_STRING};
    for (int i = 0; i < 4; ++i) {
        set_table_entry(NT_STATEMENT, decl_tokens[i], 4);
        set_table_entry(NT_DECLARATION_STATEMENT, decl_tokens[i], 14);
        set_table_entry(NT_TYPE, decl_tokens[i], 22 + i);
    }
    set_table_entry(NT_DECLARATION_TAIL, T_ASSIGN, 15);
    set_table_entry(NT_DECLARATION_TAIL, T_SEMI, 16);

    set_table_entry(NT_STATEMENT, T_IDENTIFIER, 5);
    set_table_entry(NT_ASSIGNMENT_STATEMENT, T_IDENTIFIER, 17);

    set_table_entry(NT_STATEMENT, T_IF, 6);
    set_table_entry(NT_IF_STATEMENT, T_IF, 10);

    set_table_entry(NT_STATEMENT, T_WHILE, 7);
    set_table_entry(NT_WHILE_STATEMENT, T_WHILE, 13);

    set_table_entry(NT_STATEMENT, T_WRITE, 8);
    set_table_entry(NT_STATEMENT, T_READ, 8);
    set_table_entry(NT_IO_STATEMENT, T_WRITE, 18);
    set_table_entry(NT_IO_STATEMENT, T_READ, 19);

    set_table_entry(NT_STATEMENT, T_AREA_TRIANGLE, 9);
    set_table_entry(NT_STATEMENT, T_PYTHAGORAS, 9);
    set_table_entry(NT_GEOMETRY_STATEMENT, T_AREA_TRIANGLE, 20);
    set_table_entry(NT_GEOMETRY_STATEMENT, T_PYTHAGORAS, 21);

    set_table_entry(NT_IF_STATEMENT_TAIL, T_ELSE, 11);
    Terminal after_if_tokens[] = {
        T_INT, T_FLOAT, T_CHAR, T_STRING,
        T_IDENTIFIER, T_IF, T_WHILE, T_WRITE,
        T_READ, T_AREA_TRIANGLE, T_PYTHAGORAS, T_EOF
    };
    int after_if_count = (int)(sizeof(after_if_tokens) / sizeof(after_if_tokens[0]));
    for (int i = 0; i < after_if_count; ++i) {
        set_table_entry(NT_IF_STATEMENT_TAIL, after_if_tokens[i], 12);
    }

    // condition + rel_op mapping
    Terminal expr_first[] = {
        T_IDENTIFIER, T_INT_CONST, T_FLOAT_CONST, T_CHAR_CONST, T_STRING_CONST,
        T_SQRT, T_AREA_TRIANGLE, T_PYTHAGORAS, T_LPAREN, T_MINUS
    };
    int expr_first_count = (int)(sizeof(expr_first) / sizeof(expr_first[0]));
    for (int i = 0; i < expr_first_count; ++i) {
        set_table_entry(NT_CONDITION, expr_first[i], 26);
        set_table_entry(NT_EXPRESSION, expr_first[i], 33);
        set_table_entry(NT_TERM, expr_first[i], 37);
        set_table_entry(NT_FACTOR, expr_first[i], 42 + i); // careful: indices align with factor productions
    }

    set_table_entry(NT_REL_OP, T_EQ, 27);
    set_table_entry(NT_REL_OP, T_NEQ, 28);
    set_table_entry(NT_REL_OP, T_LT, 29);
    set_table_entry(NT_REL_OP, T_GT, 30);
    set_table_entry(NT_REL_OP, T_LE, 31);
    set_table_entry(NT_REL_OP, T_GE, 32);

    set_table_entry(NT_EXPRESSION_TAIL, T_PLUS, 34);
    set_table_entry(NT_EXPRESSION_TAIL, T_MINUS, 35);
    Terminal expr_follow[] = {
        T_SEMI, T_COMMA, T_RPAREN,
        T_EQ, T_NEQ, T_LT, T_GT, T_LE, T_GE
    };
    int expr_follow_count = (int)(sizeof(expr_follow) / sizeof(expr_follow[0]));
    for (int i = 0; i < expr_follow_count; ++i) {
        set_table_entry(NT_EXPRESSION_TAIL, expr_follow[i], 36);
        set_table_entry(NT_TERM_TAIL, expr_follow[i], 41);
    }
    for (int i = 0; i < statement_starters_count; ++i) {
        set_table_entry(NT_EXPRESSION_TAIL, statement_starters[i], 36);
        set_table_entry(NT_TERM_TAIL, statement_starters[i], 41);
    }
    set_table_entry(NT_TERM_TAIL, T_PLUS, 41);
    set_table_entry(NT_TERM_TAIL, T_MINUS, 41);
    set_table_entry(NT_TERM_TAIL, T_MUL, 38);
    set_table_entry(NT_TERM_TAIL, T_DIV, 39);
    set_table_entry(NT_TERM_TAIL, T_MOD, 40);

    set_table_entry(NT_TERM_TAIL, T_MUL, 38);
    set_table_entry(NT_TERM_TAIL, T_DIV, 39);
    set_table_entry(NT_TERM_TAIL, T_MOD, 40);

    grammar_ready = 1;
}

// Dynamic arrays helpers
static void ensure_node_capacity(ParseResult *result) {
    if (result->node_count >= result->nodes_cap) {
        int new_cap = result->nodes_cap == 0 ? 32 : result->nodes_cap * 2;
        ParseNode *next = (ParseNode *)realloc(result->nodes, (size_t)new_cap * sizeof(ParseNode));
        if (!next) {
            fprintf(stderr, "Memory allocation failed for parse nodes\n");
            exit(EXIT_FAILURE);
        }
        result->nodes = next;
        result->nodes_cap = new_cap;
    }
}

static void ensure_production_capacity(ParseResult *result) {
    if (result->production_count >= result->productions_cap) {
        int new_cap = result->productions_cap == 0 ? 32 : result->productions_cap * 2;
        int *next = (int *)realloc(result->productions, (size_t)new_cap * sizeof(int));
        if (!next) {
            fprintf(stderr, "Memory allocation failed for productions\n");
            exit(EXIT_FAILURE);
        }
        result->productions = next;
        result->productions_cap = new_cap;
    }
}

static int add_node(ParseResult *result, NodeKind kind, int symbol_id, int parent) {
    ensure_node_capacity(result);
    ParseNode *node = &result->nodes[result->node_count];
    node->id = result->node_count;
    node->kind = kind;
    node->symbol_id = symbol_id;
    node->parent = parent;
    node->sibling = -1;
    result->node_count += 1;
    return node->id;
}

static void push_production(ParseResult *result, int production_index) {
    ensure_production_capacity(result);
    result->productions[result->production_count++] = production_index;
}

static void describe_expected(NonTerminal nt, char *buffer, size_t size) {
    buffer[0] = '\0';
    int wrote = 0;
    for (int t = 0; t < T_COUNT; ++t) {
        if (parse_table[nt][t] >= 0) {
            if (wrote) {
                strncat(buffer, ", ", size - strlen(buffer) - 1);
            }
            strncat(buffer, terminal_name((Terminal)t), size - strlen(buffer) - 1);
            wrote = 1;
        }
    }
}

void free_parse_result(ParseResult *result) {
    if (!result) {
        return;
    }
    free(result->nodes);
    free(result->productions);
    memset(result, 0, sizeof(*result));
}

int parse_tokens(const Terminal *tokens, size_t length, ParseResult *result, char *error_msg, size_t error_size) {
    if (!tokens || !result) {
        return 0;
    }
    build_grammar();

    result->nodes = NULL;
    result->node_count = 0;
    result->nodes_cap = 0;
    result->productions = NULL;
    result->production_count = 0;
    result->productions_cap = 0;

    int root_id = add_node(result, NODE_NONTERMINAL, NT_PROGRAM, -1);

    StackEntry stack[512];
    int top = 0;
    stack[top++] = (StackEntry){SYMBOL_TERMINAL, T_EOF, -1};
    stack[top++] = (StackEntry){SYMBOL_NONTERMINAL, NT_PROGRAM, root_id};

    size_t index = 0;
    Terminal lookahead = length > 0 ? tokens[0] : T_EOF;

    while (top > 0) {
        StackEntry current = stack[--top];
        if (current.type == SYMBOL_TERMINAL) {
            if (current.value != lookahead) {
                if (error_msg && error_size) {
                    snprintf(error_msg, error_size, "Unexpected token %s", terminal_name(lookahead));
                }
                free_parse_result(result);
                return 0;
            }
            if (lookahead != T_EOF) {
                index += 1;
                lookahead = (index < length) ? tokens[index] : T_EOF;
            }
        } else {
            int prod_index = parse_table[current.value][lookahead];
            if (prod_index < 0) {
                if (error_msg && error_size) {
                    char expected[256];
                    describe_expected((NonTerminal)current.value, expected, sizeof(expected));
                    snprintf(error_msg, error_size, "No rule for %s with lookahead %s. Expected one of: %s",
                             nonterminal_name((NonTerminal)current.value),
                             terminal_name(lookahead),
                             expected[0] ? expected : "<none>");
                }
                free_parse_result(result);
                return 0;
            }
            const Production *prod = &productions[prod_index];
            push_production(result, prod_index);

            if (prod->rhs_len == 0) {
                continue;
            }

            int child_ids[8];
            for (int i = 0; i < prod->rhs_len; ++i) {
                NodeKind kind = (prod->rhs[i].type == SYMBOL_TERMINAL) ? NODE_TERMINAL : NODE_NONTERMINAL;
                child_ids[i] = add_node(result, kind, prod->rhs[i].value, current.node_id);
            }
            for (int i = 0; i < prod->rhs_len - 1; ++i) {
                result->nodes[child_ids[i]].sibling = child_ids[i + 1];
            }
            for (int i = prod->rhs_len - 1; i >= 0; --i) {
                stack[top++] = (StackEntry){prod->rhs[i].type, prod->rhs[i].value, child_ids[i]};
            }
        }
    }

    if (lookahead != T_EOF) {
        if (error_msg && error_size) {
            snprintf(error_msg, error_size, "Input not fully consumed. Remaining token: %s", terminal_name(lookahead));
        }
        free_parse_result(result);
        return 0;
    }

    return 1;
}

static Terminal terminal_from_token_code(int code) {
    switch (code) {
        case TK_IDENTIFIER: return T_IDENTIFIER;
        case TK_INT_CONST: return T_INT_CONST;
        case TK_FLOAT_CONST: return T_FLOAT_CONST;
        case TK_CHAR_CONST: return T_CHAR_CONST;
        case TK_STRING_CONST: return T_STRING_CONST;
        case TK_IF: return T_IF;
        case TK_ELSE: return T_ELSE;
        case TK_WHILE: return T_WHILE;
        case TK_READ: return T_READ;
        case TK_WRITE: return T_WRITE;
        case TK_INT: return T_INT;
        case TK_FLOAT: return T_FLOAT;
        case TK_CHAR: return T_CHAR;
        case TK_STRING: return T_STRING;
        case TK_SQRT: return T_SQRT;
        case TK_AREA_TRIANGLE: return T_AREA_TRIANGLE;
        case TK_PYTHAGORAS: return T_PYTHAGORAS;
        case TK_ASSIGN: return T_ASSIGN;
        case TK_EQ: return T_EQ;
        case TK_NEQ: return T_NEQ;
        case TK_LT: return T_LT;
        case TK_GT: return T_GT;
        case TK_LE: return T_LE;
        case TK_GE: return T_GE;
        case TK_PLUS: return T_PLUS;
        case TK_MINUS: return T_MINUS;
        case TK_MUL: return T_MUL;
        case TK_DIV: return T_DIV;
        case TK_MOD: return T_MOD;
        case TK_LPAREN: return T_LPAREN;
        case TK_RPAREN: return T_RPAREN;
        case TK_LBRACE: return T_LBRACE;
        case TK_RBRACE: return T_RBRACE;
        case TK_SEMI: return T_SEMI;
        case TK_COMMA: return T_COMMA;
        default:
            return (Terminal)(-1);
    }
}

int load_tokens_from_pif(const char *path, Terminal **out_tokens, size_t *out_length, char *error_msg, size_t error_size) {
    if (!path || !out_tokens || !out_length) {
        return 0;
    }
    FILE *f = fopen(path, "r");
    if (!f) {
        if (error_msg && error_size) {
            snprintf(error_msg, error_size, "Failed to open PIF file: %s", strerror(errno));
        }
        return 0;
    }

    Terminal *buffer = NULL;
    size_t len = 0;
    size_t cap = 0;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char *ptr = line;
        while (*ptr && isspace((unsigned char)*ptr)) {
            ++ptr;
        }
        if (*ptr == '\0' || *ptr == '#') {
            continue;
        }
        char *endptr = NULL;
        long code = strtol(ptr, &endptr, 10);
        if (ptr == endptr) {
            continue;
        }
        Terminal term = terminal_from_token_code((int)code);
        if ((int)term < 0) {
            fclose(f);
            free(buffer);
            if (error_msg && error_size) {
                snprintf(error_msg, error_size, "Unsupported token code %ld in PIF", code);
            }
            return 0;
        }
        if (len >= cap) {
            size_t new_cap = cap == 0 ? 64 : cap * 2;
            Terminal *tmp = (Terminal *)realloc(buffer, new_cap * sizeof(Terminal));
            if (!tmp) {
                fclose(f);
                free(buffer);
                if (error_msg && error_size) {
                    snprintf(error_msg, error_size, "Memory allocation failure while loading PIF");
                }
                return 0;
            }
            buffer = tmp;
            cap = new_cap;
        }
        buffer[len++] = term;
    }
    fclose(f);

    if (len >= cap) {
        Terminal *tmp = (Terminal *)realloc(buffer, (cap + 1) * sizeof(Terminal));
        if (!tmp) {
            free(buffer);
            if (error_msg && error_size) {
                snprintf(error_msg, error_size, "Memory allocation failure while finalizing tokens");
            }
            return 0;
        }
        buffer = tmp;
        cap += 1;
    }
    buffer[len++] = T_EOF;

    *out_tokens = buffer;
    *out_length = len;
    return 1;
}

static Terminal terminal_from_name(const char *raw) {
    if (!raw) {
        return (Terminal)(-1);
    }
    char token[64];
    size_t n = strlen(raw);
    if (n >= sizeof(token)) {
        return (Terminal)(-1);
    }
    for (size_t i = 0; i < n; ++i) {
        token[i] = (char)tolower((unsigned char)raw[i]);
    }
    token[n] = '\0';

    if (strcmp(token, "id") == 0 || strcmp(token, "identifier") == 0) return T_IDENTIFIER;
    if (strcmp(token, "int_const") == 0) return T_INT_CONST;
    if (strcmp(token, "float_const") == 0) return T_FLOAT_CONST;
    if (strcmp(token, "char_const") == 0) return T_CHAR_CONST;
    if (strcmp(token, "string_const") == 0) return T_STRING_CONST;
    if (strcmp(token, "if") == 0) return T_IF;
    if (strcmp(token, "else") == 0) return T_ELSE;
    if (strcmp(token, "while") == 0) return T_WHILE;
    if (strcmp(token, "read") == 0) return T_READ;
    if (strcmp(token, "write") == 0) return T_WRITE;
    if (strcmp(token, "int") == 0) return T_INT;
    if (strcmp(token, "float") == 0) return T_FLOAT;
    if (strcmp(token, "char") == 0) return T_CHAR;
    if (strcmp(token, "string") == 0) return T_STRING;
    if (strcmp(token, "sqrt") == 0) return T_SQRT;
    if (strcmp(token, "area_triangle") == 0) return T_AREA_TRIANGLE;
    if (strcmp(token, "pythagoras") == 0) return T_PYTHAGORAS;
    if (strcmp(token, "=") == 0) return T_ASSIGN;
    if (strcmp(token, "==") == 0) return T_EQ;
    if (strcmp(token, "!=") == 0) return T_NEQ;
    if (strcmp(token, "<") == 0) return T_LT;
    if (strcmp(token, ">") == 0) return T_GT;
    if (strcmp(token, "<=") == 0) return T_LE;
    if (strcmp(token, ">=") == 0) return T_GE;
    if (strcmp(token, "+") == 0) return T_PLUS;
    if (strcmp(token, "-") == 0) return T_MINUS;
    if (strcmp(token, "*") == 0) return T_MUL;
    if (strcmp(token, "/") == 0) return T_DIV;
    if (strcmp(token, "%") == 0) return T_MOD;
    if (strcmp(token, "(") == 0) return T_LPAREN;
    if (strcmp(token, ")") == 0) return T_RPAREN;
    if (strcmp(token, "{") == 0) return T_LBRACE;
    if (strcmp(token, "}") == 0) return T_RBRACE;
    if (strcmp(token, ";") == 0) return T_SEMI;
    if (strcmp(token, ",") == 0) return T_COMMA;
    if (strcmp(token, "eof") == 0) return T_EOF;
    return (Terminal)(-1);
}

int load_tokens_from_stream(const char *path, Terminal **out_tokens, size_t *out_length, char *error_msg, size_t error_size) {
    if (!path || !out_tokens || !out_length) {
        return 0;
    }
    FILE *f = fopen(path, "r");
    if (!f) {
        if (error_msg && error_size) {
            snprintf(error_msg, error_size, "Failed to open tokens file: %s", strerror(errno));
        }
        return 0;
    }

    Terminal *buffer = NULL;
    size_t len = 0;
    size_t cap = 0;
    char token[64];
    while (fscanf(f, "%63s", token) == 1) {
        Terminal t = terminal_from_name(token);
        if ((int)t < 0) {
            fclose(f);
            free(buffer);
            if (error_msg && error_size) {
                snprintf(error_msg, error_size, "Unsupported token %s in stream", token);
            }
            return 0;
        }
        if (len >= cap) {
            size_t new_cap = cap == 0 ? 64 : cap * 2;
            Terminal *tmp = (Terminal *)realloc(buffer, new_cap * sizeof(Terminal));
            if (!tmp) {
                fclose(f);
                free(buffer);
                if (error_msg && error_size) {
                    snprintf(error_msg, error_size, "Memory allocation failure while loading stream");
                }
                return 0;
            }
            buffer = tmp;
            cap = new_cap;
        }
        buffer[len++] = t;
    }
    fclose(f);

    if (len == 0 || buffer[len - 1] != T_EOF) {
        if (len >= cap) {
            Terminal *tmp = (Terminal *)realloc(buffer, (cap + 1) * sizeof(Terminal));
            if (!tmp) {
                free(buffer);
                if (error_msg && error_size) {
                    snprintf(error_msg, error_size, "Failed to append EOF token");
                }
                return 0;
            }
            buffer = tmp;
            cap += 1;
        }
        buffer[len++] = T_EOF;
    }

    *out_tokens = buffer;
    *out_length = len;
    return 1;
}

int ensure_directory(const char *path) {
    if (!path) {
        return 0;
    }
    struct stat st;
    if (stat(path, &st) == 0) {
        return (st.st_mode & S_IFDIR) != 0;
    }
#ifdef _WIN32
    return _mkdir(path) == 0;
#else
    return mkdir(path, 0755) == 0;
#endif
}

const char *nonterminal_name(NonTerminal nt) {
    switch (nt) {
        case NT_PROGRAM: return "program";
        case NT_STATEMENT_LIST: return "statement_list";
        case NT_STATEMENT_LIST_TAIL: return "statement_list_tail";
        case NT_STATEMENT: return "statement";
        case NT_IF_STATEMENT_TAIL: return "if_statement_tail";
        case NT_DECLARATION_STATEMENT: return "declaration_statement";
        case NT_DECLARATION_TAIL: return "declaration_tail";
        case NT_ASSIGNMENT_STATEMENT: return "assignment_statement";
        case NT_IF_STATEMENT: return "if_statement";
        case NT_WHILE_STATEMENT: return "while_statement";
        case NT_IO_STATEMENT: return "io_statement";
        case NT_GEOMETRY_STATEMENT: return "geometry_statement";
        case NT_TYPE: return "type";
        case NT_CONDITION: return "condition";
        case NT_REL_OP: return "relational_operator";
        case NT_EXPRESSION: return "expression";
        case NT_EXPRESSION_TAIL: return "expression_tail";
        case NT_TERM: return "term";
        case NT_TERM_TAIL: return "term_tail";
        case NT_FACTOR: return "factor";
        default: return "unknown_nonterminal";
    }
}

const char *terminal_name(Terminal t) {
    switch (t) {
        case T_IDENTIFIER: return "identifier";
        case T_INT_CONST: return "int_const";
        case T_FLOAT_CONST: return "float_const";
        case T_CHAR_CONST: return "char_const";
        case T_STRING_CONST: return "string_const";
        case T_IF: return "if";
        case T_ELSE: return "else";
        case T_WHILE: return "while";
        case T_READ: return "read";
        case T_WRITE: return "write";
        case T_INT: return "int";
        case T_FLOAT: return "float";
        case T_CHAR: return "char";
        case T_STRING: return "string";
        case T_SQRT: return "sqrt";
        case T_AREA_TRIANGLE: return "area_triangle";
        case T_PYTHAGORAS: return "pythagoras";
        case T_ASSIGN: return "=";
        case T_EQ: return "==";
        case T_NEQ: return "!=";
        case T_LT: return "<";
        case T_GT: return ">";
        case T_LE: return "<=";
        case T_GE: return ">=";
        case T_PLUS: return "+";
        case T_MINUS: return "-";
        case T_MUL: return "*";
        case T_DIV: return "/";
        case T_MOD: return "%";
        case T_LPAREN: return "(";
        case T_RPAREN: return ")";
        case T_LBRACE: return "{";
        case T_RBRACE: return "}";
        case T_SEMI: return ";";
        case T_COMMA: return ",";
        case T_EOF: return "EOF";
        default: return "unknown_terminal";
    }
}

const char *production_text(int index) {
    if (index < 0 || index >= production_count) {
        return "invalid production";
    }
    return productions[index].text;
}

int write_productions_file(const ParseResult *result, const char *path) {
    if (!result || !path) {
        return 0;
    }
    FILE *f = fopen(path, "w");
    if (!f) {
        return 0;
    }
    for (int i = 0; i < result->production_count; ++i) {
        fprintf(f, "%s\n", production_text(result->productions[i]));
    }
    fclose(f);
    return 1;
}

int write_parse_tree_table_file(const ParseResult *result, const char *path) {
    if (!result || !path) {
        return 0;
    }
    FILE *f = fopen(path, "w");
    if (!f) {
        return 0;
    }
    fprintf(f, "id,symbol,parent,sibling,kind\n");
    for (int i = 0; i < result->node_count; ++i) {
        const ParseNode *node = &result->nodes[i];
        const char *name = node->kind == NODE_TERMINAL
                               ? terminal_name((Terminal)node->symbol_id)
                               : nonterminal_name((NonTerminal)node->symbol_id);
        fprintf(f, "%d,%s,%d,%d,%s\n",
                node->id,
                name,
                node->parent,
                node->sibling,
                node->kind == NODE_TERMINAL ? "terminal" : "nonterminal");
    }
    fclose(f);
    return 1;
}


