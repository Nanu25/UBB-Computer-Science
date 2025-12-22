# Lab 6: Syntax Analysis with Flex + Bison

## Overview
This lab implements a syntax analyzer using **Flex** (lexical analyzer) and **Bison** (parser generator) for the mini geometry DSL.

## Requirements
- **Flex** (or WinFlexBison on Windows)
- **Bison** (or WinFlexBison on Windows)  
- **GCC** compiler

## Project Structure
```
lab6/
├── src/
│   ├── parser.y          # Bison grammar file
│   ├── scanner.l         # Flex scanner (returns tokens)
│   ├── main.c            # Main driver
│   └── productions.c     # Production tracking
├── include/
│   ├── tokens.h          # Token definitions
│   └── productions.h     # Production tracking interface
└── Makefile
```

## Building
```bash
cd lab6
make
```

This will:
1. Run Bison on `parser.y` to generate `parser.tab.c` and `parser.tab.h`
2. Run Flex on `scanner.l` to generate `lex.yy.c`
3. Compile all C files
4. Link into `flcd_parser` executable

## Running
```bash
./flcd_parser <input_file>
```

Example:
```bash
./flcd_parser ../geometry2LFTC.txt
```

## Output
- **productions.txt**: Contains all production rules applied during parsing (one per line)

## How It Works

### 1. Lexical Analysis (Flex)
The scanner (`scanner.l`) recognizes tokens and returns token codes to the parser. It matches:
- Keywords (if, else, while, read, write, etc.)
- Operators (+, -, *, /, ==, !=, etc.)
- Identifiers and constants
- Separators (parentheses, semicolons, commas)

### 2. Syntax Analysis (Bison)
The parser (`parser.y`) defines the grammar rules:
- Each production rule has an action that records itself via `add_production()`
- The parser builds a parse tree implicitly while matching rules
- Operator precedence is handled via `%left`, `%right`, `%nonassoc`

### 3. Production Tracking
The `productions.c` module:
- Maintains a buffer of all production rules applied
- Writes them to `productions.txt` after successful parsing

## Grammar Rules
The parser implements the grammar from `BNF.txt`:
- `program → statement_list`
- `statement_list → statement | statement_list statement`
- `statement → declaration_statement | assignment_statement | if_statement | while_statement | io_statement | geometry_statement`
- `expression → term | expression + term | expression - term`
- `term → factor | term * factor | term / factor | term % factor`
- `factor → identifier | constant | sqrt(expression) | (expression)`
- And more...

## Example Productions Output
```
program -> statement_list
statement_list -> statement
statement -> declaration_statement
declaration_statement -> type identifier = expression ;
type -> float
expression -> term
term -> factor
factor -> int_const
...
```

## Error Handling
- **Lexical errors**: Reported by the scanner for unrecognized characters
- **Syntax errors**: Reported by Bison's `yyerror()` function when input doesn't match grammar

## Cleanup
```bash
make clean
```
Removes all generated files and object files.

