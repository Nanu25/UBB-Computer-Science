# Lab 7: LL(1) Parser Implementation

This lab implements an LL(1) parser for the mini-DSL grammar. It parses token sequences and builds a parse tree using the father/sibling representation.

## Building

```bash
cd lab7
make
```

This compiles both parsers:
- `ll1_parser.exe` - for the mini-DSL grammar
- `seminar_parser.exe` - for the seminar grammar (requirement 1)

## Running

### Mini-DSL Parser (Requirement 2)

Parse a PIF file:
```bash
./ll1_parser --input ../pif.txt --mode pif --output out
```

Or parse a token stream file:
```bash
./ll1_parser --input samples/tokens.txt --mode tokens --output out
```

Output files:
- `out/productions.txt` - list of productions applied during parsing
- `out/parse_tree.csv` - parse tree as a table with id, symbol, parent, sibling, kind

### Seminar Parser (Requirement 1)

```bash
./seminar_parser --input samples/seminar_tokens.txt --output out
```

The input file should contain space-separated tokens: `a`, `(`, `)`, `+`, `*`. EOF is added automatically.

Output files:
- `out/seminar_productions.txt` - production sequence
- `out/seminar_parse_tree.csv` - parse tree table

## Understanding the Parse Tree CSV

The CSV represents the parse tree using parent and sibling links. Each row is a node:

- `id` - unique identifier for the node
- `symbol` - the grammar symbol (nonterminal like `program`, `statement` or terminal like `identifier`, `;`)
- `parent` - id of the parent node (-1 means it's the root)
- `sibling` - id of the next sibling node (-1 means it's the last child)
- `kind` - either "nonterminal" or "terminal"

Example: For `a * (a + a)`, the tree shows:
- Root `S` expands to `B A`
- `B` expands to `D C` which handles `a * (a + a)`
- The `*` operator is a child of `C`
- The parenthesized `(a + a)` is under another `D` node

To navigate: follow `parent` links to go up the tree, use `sibling` to move to the next child at the same level.

## How It Works

The parser uses a standard LL(1) algorithm:

1. Initialize stack with EOF and start symbol
2. While stack is not empty:
   - If top is a terminal: match with input token
   - If top is a nonterminal: lookup production in parse table, push RHS symbols
3. Build parse tree nodes as productions are applied
4. Link parent/sibling relationships

The parsing table is built from FIRST/FOLLOW sets. Left recursion was removed from the grammar (e.g., `expression -> term expression'` instead of `expression -> expression + term`).

## Files

- `src/ll1_parser.c` - main parser for mini-DSL
- `src/seminar_parser.c` - parser for seminar grammar
- `src/main.c` - command-line interface
- `include/ll1_parser.h` - parser interface
- `samples/` - example input files

## Notes

- Token codes from PIF map directly to terminals using `tokens.h`
- The parse tree is built incrementally during parsing
- Both parsers use the same algorithm, just different grammars
- Epsilon productions (ε) don't create tree nodes but allow parsing to continue
