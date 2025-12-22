%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "st.h"
#include "tokens.h"
#include "fa_validate.h"

extern FILE *pifFile;
extern FILE *errFile;
extern SymbolTable *globalST;

static void pif_emit(int tokenCode, int bucketIndex, int chainIndex) {
    if (pifFile) {
        fprintf(pifFile, "%d %d %d\n", tokenCode, bucketIndex, chainIndex);
    }
}

static void report_error(const char *msg) {
    if (errFile) {
        fprintf(errFile, "Lexical error at line %d: %s (got '%s')\n", yylineno, msg, yytext);
    }
}
%}

%option noyywrap yylineno nodefault

DIGIT              [0-9]
NON_ZERO_DIGIT     [1-9]
LETTER             [a-zA-Z]
UNDERSCORE         _
ID                 {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
INT_CONST          0|[-]?{NON_ZERO_DIGIT}{DIGIT}*
FLOAT_CONST        [-]?{DIGIT}+\.({DIGIT}+)
CHAR_CONST         '\'[a-zA-Z0-9_]\'
STRING_CONST       \"([^\"\n]|\\.)*\"
WS                 [ \t\r\n]+

%%

"if"            { pif_emit(TK_IF, -1, -1); }
"else"          { pif_emit(TK_ELSE, -1, -1); }
"while"         { pif_emit(TK_WHILE, -1, -1); }
"read"          { pif_emit(TK_READ, -1, -1); }
"write"         { pif_emit(TK_WRITE, -1, -1); }
"int"           { pif_emit(TK_INT, -1, -1); }
"float"         { pif_emit(TK_FLOAT, -1, -1); }
"char"          { pif_emit(TK_CHAR, -1, -1); }
"string"        { pif_emit(TK_STRING, -1, -1); }
"const"         { pif_emit(TK_CONST, -1, -1); }
"sqrt"          { pif_emit(TK_SQRT, -1, -1); }
"area_triangle" { pif_emit(TK_AREA_TRIANGLE, -1, -1); }
"pythagoras"    { pif_emit(TK_PYTHAGORAS, -1, -1); }

"=="            { pif_emit(TK_EQ, -1, -1); }
"!="            { pif_emit(TK_NEQ, -1, -1); }
"<="            { pif_emit(TK_LE, -1, -1); }
">="            { pif_emit(TK_GE, -1, -1); }
"&&"            { pif_emit(TK_AND, -1, -1); }
"||"            { pif_emit(TK_OR, -1, -1); }
"="             { pif_emit(TK_ASSIGN, -1, -1); }
"<"             { pif_emit(TK_LT, -1, -1); }
">"             { pif_emit(TK_GT, -1, -1); }
"+"             { pif_emit(TK_PLUS, -1, -1); }
"-"             { pif_emit(TK_MINUS, -1, -1); }
"*"             { pif_emit(TK_MUL, -1, -1); }
"/"             { pif_emit(TK_DIV, -1, -1); }
"%"             { pif_emit(TK_MOD, -1, -1); }

"("             { pif_emit(TK_LPAREN, -1, -1); }
")"             { pif_emit(TK_RPAREN, -1, -1); }
"{"             { pif_emit(TK_LBRACE, -1, -1); }
"}"             { pif_emit(TK_RBRACE, -1, -1); }
";"             { pif_emit(TK_SEMI, -1, -1); }
","             { pif_emit(TK_COMMA, -1, -1); }

{FLOAT_CONST}    {
                    STEntry *e = st_insert(globalST, yytext);
                    if (!e) { report_error("Out of memory on float const"); }
                    pif_emit(TK_FLOAT_CONST, e ? e->bucketIndex : -1, e ? e->chainIndex : -1);
                 }
{INT_CONST}      {
                    if (!fa_accept_int_const(yytext)) {
                        report_error("INT_CONST failed FA validation");
                    }
                    STEntry *e = st_insert(globalST, yytext);
                    if (!e) { report_error("Out of memory on int const"); }
                    pif_emit(TK_INT_CONST, e ? e->bucketIndex : -1, e ? e->chainIndex : -1);
                 }
{CHAR_CONST}     {
                    STEntry *e = st_insert(globalST, yytext);
                    if (!e) { report_error("Out of memory on char const"); }
                    pif_emit(TK_CHAR_CONST, e ? e->bucketIndex : -1, e ? e->chainIndex : -1);
                 }
{STRING_CONST}   {
                    STEntry *e = st_insert(globalST, yytext);
                    if (!e) { report_error("Out of memory on string const"); }
                    pif_emit(TK_STRING_CONST, e ? e->bucketIndex : -1, e ? e->chainIndex : -1);
                 }
{ID}             {
                    if (!fa_accept_identifier(yytext)) {
                        report_error("IDENTIFIER failed FA validation");
                    }
                    STEntry *e = st_insert(globalST, yytext);
                    if (!e) { report_error("Out of memory on identifier"); }
                    pif_emit(TK_IDENTIFIER, e ? e->bucketIndex : -1, e ? e->chainIndex : -1);
                 }

"{"[^}\n]*"}"   { /* ignore one-line Pascal-like comment */ }
"//".*          { /* ignore line comment */ }
{WS}            { /* skip whitespace */ }

.               { report_error("Unrecognized character"); }

%%
