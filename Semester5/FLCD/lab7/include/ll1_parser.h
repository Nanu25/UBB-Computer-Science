#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include <stddef.h>

typedef enum {
    T_IDENTIFIER = 0,
    T_INT_CONST,
    T_FLOAT_CONST,
    T_CHAR_CONST,
    T_STRING_CONST,
    T_IF,
    T_ELSE,
    T_WHILE,
    T_READ,
    T_WRITE,
    T_INT,
    T_FLOAT,
    T_CHAR,
    T_STRING,
    T_SQRT,
    T_AREA_TRIANGLE,
    T_PYTHAGORAS,
    T_ASSIGN,
    T_EQ,
    T_NEQ,
    T_LT,
    T_GT,
    T_LE,
    T_GE,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV,
    T_MOD,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_SEMI,
    T_COMMA,
    T_EOF,
    T_COUNT
} Terminal;

typedef enum {
    NT_PROGRAM = 0,
    NT_STATEMENT_LIST,
    NT_STATEMENT_LIST_TAIL,
    NT_STATEMENT,
    NT_IF_STATEMENT_TAIL,
    NT_DECLARATION_STATEMENT,
    NT_DECLARATION_TAIL,
    NT_ASSIGNMENT_STATEMENT,
    NT_IF_STATEMENT,
    NT_WHILE_STATEMENT,
    NT_IO_STATEMENT,
    NT_GEOMETRY_STATEMENT,
    NT_TYPE,
    NT_CONDITION,
    NT_REL_OP,
    NT_EXPRESSION,
    NT_EXPRESSION_TAIL,
    NT_TERM,
    NT_TERM_TAIL,
    NT_FACTOR,
    NT_COUNT
} NonTerminal;

typedef enum {
    NODE_NONTERMINAL = 0,
    NODE_TERMINAL
} NodeKind;

typedef struct {
    int id;
    NodeKind kind;
    int symbol_id;
    int parent;
    int sibling;
} ParseNode;

typedef struct {
    ParseNode *nodes;
    int node_count;
    int nodes_cap;

    int *productions;
    int production_count;
    int productions_cap;
} ParseResult;

int parse_tokens(const Terminal *tokens, size_t length, ParseResult *result, char *error_msg, size_t error_size);
void free_parse_result(ParseResult *result);
int load_tokens_from_pif(const char *path, Terminal **out_tokens, size_t *out_length, char *error_msg, size_t error_size);
int load_tokens_from_stream(const char *path, Terminal **out_tokens, size_t *out_length, char *error_msg, size_t error_size);
int ensure_directory(const char *path);
const char *production_text(int index);
const char *terminal_name(Terminal t);
const char *nonterminal_name(NonTerminal nt);
int write_productions_file(const ParseResult *result, const char *path);
int write_parse_tree_table_file(const ParseResult *result, const char *path);

#endif /* LL1_PARSER_H */


