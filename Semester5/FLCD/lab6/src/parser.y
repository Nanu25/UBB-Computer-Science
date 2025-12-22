%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/productions.h"

// Global variables for production tracking
extern char productions_buffer[10000];
extern int productions_count;

// Function to add production to output
void add_production(const char* prod);

int yyerror(const char *s);
int yylex(void);
extern FILE *yyin;
%}

%token TK_IDENTIFIER TK_INT_CONST TK_FLOAT_CONST TK_CHAR_CONST TK_STRING_CONST
%token TK_IF TK_ELSE TK_WHILE TK_READ TK_WRITE
%token TK_INT TK_FLOAT TK_CHAR TK_STRING TK_CONST
%token TK_SQRT TK_AREA_TRIANGLE TK_PYTHAGORAS
%token TK_ASSIGN TK_EQ TK_NEQ TK_LT TK_GT TK_LE TK_GE
%token TK_AND TK_OR
%token TK_PLUS TK_MINUS TK_MUL TK_DIV TK_MOD
%token TK_LPAREN TK_RPAREN TK_LBRACE TK_RBRACE TK_SEMI TK_COMMA

%left TK_OR
%left TK_AND
%nonassoc TK_LT TK_GT TK_LE TK_GE TK_EQ TK_NEQ
%left TK_PLUS TK_MINUS
%left TK_MUL TK_DIV TK_MOD
%right UMINUS

%%

program:
    statement_list
    {
        add_production("program -> statement_list");
    }
    ;

statement_list:
    statement
    {
        add_production("statement_list -> statement");
    }
    | statement_list statement
    {
        add_production("statement_list -> statement_list statement");
    }
    ;

statement:
    declaration_statement
    {
        add_production("statement -> declaration_statement");
    }
    | assignment_statement
    {
        add_production("statement -> assignment_statement");
    }
    | if_statement
    {
        add_production("statement -> if_statement");
    }
    | while_statement
    {
        add_production("statement -> while_statement");
    }
    | io_statement
    {
        add_production("statement -> io_statement");
    }
    | geometry_statement
    {
        add_production("statement -> geometry_statement");
    }
    ;

declaration_statement:
    type TK_IDENTIFIER TK_ASSIGN expression TK_SEMI
    {
        add_production("declaration_statement -> type identifier = expression ;");
    }
    ;

assignment_statement:
    TK_IDENTIFIER TK_ASSIGN expression TK_SEMI
    {
        add_production("assignment_statement -> identifier = expression ;");
    }
    ;

if_statement:
    TK_IF condition statement
    {
        add_production("if_statement -> IF condition statement");
    }
    | TK_IF condition statement TK_ELSE statement
    {
        add_production("if_statement -> IF condition statement ELSE statement");
    }
    ;

while_statement:
    TK_WHILE condition statement
    {
        add_production("while_statement -> WHILE condition statement");
    }
    ;

io_statement:
    TK_WRITE TK_LPAREN expression TK_RPAREN TK_SEMI
    {
        add_production("io_statement -> write ( expression ) ;");
    }
    | TK_READ TK_LPAREN TK_IDENTIFIER TK_RPAREN TK_SEMI
    {
        add_production("io_statement -> read ( identifier ) ;");
    }
    ;

geometry_statement:
    TK_AREA_TRIANGLE TK_LPAREN expression TK_COMMA expression TK_RPAREN TK_SEMI
    {
        add_production("geometry_statement -> area_triangle ( expression , expression ) ;");
    }
    | TK_PYTHAGORAS TK_LPAREN expression TK_COMMA expression TK_RPAREN TK_SEMI
    {
        add_production("geometry_statement -> pythagoras ( expression , expression ) ;");
    }
    ;

type:
    TK_INT
    {
        add_production("type -> int");
    }
    | TK_FLOAT
    {
        add_production("type -> float");
    }
    | TK_CHAR
    {
        add_production("type -> char");
    }
    | TK_STRING
    {
        add_production("type -> string");
    }
    ;

condition:
    expression relational_operator expression
    {
        add_production("condition -> expression relational_operator expression");
    }
    ;

relational_operator:
    TK_EQ
    {
        add_production("relational_operator -> ==");
    }
    | TK_NEQ
    {
        add_production("relational_operator -> !=");
    }
    | TK_LT
    {
        add_production("relational_operator -> <");
    }
    | TK_GT
    {
        add_production("relational_operator -> >");
    }
    | TK_LE
    {
        add_production("relational_operator -> <=");
    }
    | TK_GE
    {
        add_production("relational_operator -> >=");
    }
    ;

expression:
    term
    {
        add_production("expression -> term");
    }
    | expression TK_PLUS term
    {
        add_production("expression -> expression + term");
    }
    | expression TK_MINUS term
    {
        add_production("expression -> expression - term");
    }
    ;

term:
    factor
    {
        add_production("term -> factor");
    }
    | term TK_MUL factor
    {
        add_production("term -> term * factor");
    }
    | term TK_DIV factor
    {
        add_production("term -> term / factor");
    }
    | term TK_MOD factor
    {
        add_production("term -> term % factor");
    }
    ;

factor:
    TK_IDENTIFIER
    {
        add_production("factor -> identifier");
    }
    | TK_INT_CONST
    {
        add_production("factor -> int_const");
    }
    | TK_FLOAT_CONST
    {
        add_production("factor -> float_const");
    }
    | TK_CHAR_CONST
    {
        add_production("factor -> char_const");
    }
    | TK_STRING_CONST
    {
        add_production("factor -> string_const");
    }
    | TK_SQRT TK_LPAREN expression TK_RPAREN
    {
        add_production("factor -> sqrt ( expression )");
    }
    | TK_AREA_TRIANGLE TK_LPAREN expression TK_COMMA expression TK_RPAREN
    {
        add_production("factor -> area_triangle ( expression , expression )");
    }
    | TK_PYTHAGORAS TK_LPAREN expression TK_COMMA expression TK_RPAREN
    {
        add_production("factor -> pythagoras ( expression , expression )");
    }
    | TK_LPAREN expression TK_RPAREN
    {
        add_production("factor -> ( expression )");
    }
    | TK_MINUS factor %prec UMINUS
    {
        add_production("factor -> - factor");
    }
    ;

%%

int yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
    return 0;
}

