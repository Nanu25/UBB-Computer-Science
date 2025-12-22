#ifndef TOKENS_H
#define TOKENS_H

// Token codes for PIF; keep stable order
enum TokenCode {
    TK_IDENTIFIER = 1,
    TK_INT_CONST = 2,
    TK_FLOAT_CONST = 3,
    TK_CHAR_CONST = 4,
    TK_STRING_CONST = 5,

    // Keywords
    TK_IF = 100,
    TK_ELSE = 101,
    TK_WHILE = 102,
    TK_READ = 103,
    TK_WRITE = 104,
    TK_INT = 105,
    TK_FLOAT = 106,
    TK_CHAR = 107,
    TK_STRING = 108,
    TK_CONST = 109,
    TK_SQRT = 110,
    TK_AREA_TRIANGLE = 111,
    TK_PYTHAGORAS = 112,

    // Operators
    TK_ASSIGN = 200,     // =
    TK_EQ = 201,         // ==
    TK_NEQ = 202,        // !=
    TK_LT = 203,         // <
    TK_GT = 204,         // >
    TK_LE = 205,         // <=
    TK_GE = 206,         // >=
    TK_AND = 207,        // &&
    TK_OR = 208,         // ||
    TK_PLUS = 209,       // +
    TK_MINUS = 210,      // -
    TK_MUL = 211,        // *
    TK_DIV = 212,        // /
    TK_MOD = 213,        // %

    // Separators
    TK_LPAREN = 300,     // (
    TK_RPAREN = 301,     // )
    TK_LBRACE = 302,     // {
    TK_RBRACE = 303,     // }
    TK_SEMI = 304,       // ;
    TK_COMMA = 305       // ,
};

#endif // TOKENS_H


