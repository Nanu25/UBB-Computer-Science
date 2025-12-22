%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

extern int yylineno;
%}

%option noyywrap yylineno nodefault

DIGIT              [0-9]
NON_ZERO_DIGIT     [1-9]
LETTER             [a-zA-Z]
UNDERSCORE         _
ID                 {LETTER}({LETTER}|{DIGIT}|{UNDERSCORE})*
INT_CONST          0|[-]?{NON_ZERO_DIGIT}{DIGIT}*
FLOAT_CONST        [-]?{DIGIT}+\.({DIGIT}+)
CHAR_CONST         '\'[a-zA-Z0-9_]\''
STRING_CONST       \"([^\"\n]|\\.)*\"
WS                 [ \t\r\n]+

%%

"if"            { return TK_IF; }
"else"          { return TK_ELSE; }
"while"         { return TK_WHILE; }
"read"           { return TK_READ; }
"write"          { return TK_WRITE; }
"int"            { return TK_INT; }
"float"          { return TK_FLOAT; }
"char"           { return TK_CHAR; }
"string"         { return TK_STRING; }
"const"          { return TK_CONST; }
"sqrt"           { return TK_SQRT; }
"area_triangle"  { return TK_AREA_TRIANGLE; }
"pythagoras"     { return TK_PYTHAGORAS; }

"=="            { return TK_EQ; }
"!="            { return TK_NEQ; }
"<="            { return TK_LE; }
">="            { return TK_GE; }
"&&"            { return TK_AND; }
"||"            { return TK_OR; }
"="             { return TK_ASSIGN; }
"<"             { return TK_LT; }
">"             { return TK_GT; }
"+"             { return TK_PLUS; }
"-"             { return TK_MINUS; }
"*"             { return TK_MUL; }
"/"             { return TK_DIV; }
"%"             { return TK_MOD; }

"("             { return TK_LPAREN; }
")"             { return TK_RPAREN; }
"{"             { return TK_LBRACE; }
"}"             { return TK_RBRACE; }
";"             { return TK_SEMI; }
","             { return TK_COMMA; }

{FLOAT_CONST}    { return TK_FLOAT_CONST; }
{INT_CONST}      { return TK_INT_CONST; }
{CHAR_CONST}     { return TK_CHAR_CONST; }
{STRING_CONST}   { return TK_STRING_CONST; }
{ID}             { return TK_IDENTIFIER; }

"{"[^}\n]*"}"   { /* ignore one-line Pascal-like comment */ }
"//".*          { /* ignore line comment */ }
{WS}            { /* skip whitespace */ }

.               { 
                    fprintf(stderr, "Lexical error at line %d: Unrecognized character '%s'\n", yylineno, yytext);
                    return yytext[0];
                }

%%

