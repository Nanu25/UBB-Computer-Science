# FA to RG Transformation Lab

## Overview
This lab implements the transformation from Finite Automata (FA) to Regular Grammars (RG) for the lexical patterns of a domain-specific programming language.

## Patterns Implemented
1. **IDENTIFIER**: `letter(letter|digit|_)*`
2. **INTEGER CONSTANT**: `0|[-]?[1-9][0-9]*`

## Files Structure
- `fa_rg.h` - Header file with data structures and function declarations
- `fa_rg.c` - Implementation of FA and RG operations
- `main.c` - Demo program showing FA to RG transformation
- `patterns.txt` - Original regex patterns
- `fa_identifier` - FA definition for identifiers
- `rg_identifiers.txt` - RG definition for identifiers
- `Makefile` - Build configuration

## Data Structures

### Finite Automaton
```c
typedef struct {
    int states[MAX_STATES];           // State numbers
    int num_states;                   // Number of states
    int start_state;                  // Start state
    int final_states[MAX_STATES];     // Final states
    int num_final_states;             // Number of final states
    char alphabet[MAX_SYMBOLS];       // Input alphabet
    int num_symbols;                  // Number of symbols
    int transitions[MAX_STATES][MAX_SYMBOLS]; // Transition table
} FiniteAutomaton;
```

### Regular Grammar
```c
typedef struct {
    char nonterminals[MAX_SYMBOLS];   // Non-terminal symbols
    int num_nonterminals;             // Number of non-terminals
    char terminals[MAX_SYMBOLS];      // Terminal symbols
    int num_terminals;                // Number of terminals
    char start_symbol;                // Start symbol
    char rules[MAX_RULES][MAX_RULE_LEN]; // Production rules
    int num_rules;                    // Number of rules
} RegularGrammar;
```

## Transformation Algorithm

The FA to RG transformation follows these rules:

1. **For each transition** `A --a--> B`: Create grammar rule `A → aB`
2. **For each final state** `F`: Create rule `F → ε`

### Example: IDENTIFIER Pattern

**Finite Automaton:**
- States: {q0, q1}
- Start: q0
- Final: {q1}
- Transitions:
  - q0 --letter--> q1
  - q1 --letter--> q1
  - q1 --digit--> q1
  - q1 --underscore--> q1

**Regular Grammar:**
- Non-terminals: {q0, q1}
- Terminals: {letter, digit, underscore}
- Start: q0
- Rules:
  1. q0 → letter q1
  2. q1 → letter q1
  3. q1 → digit q1
  4. q1 → underscore q1
  5. q1 → ε

## How to Build and Run

### Build
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

## Expected Output

The program will display:
1. Original Finite Automaton for IDENTIFIER
2. Converted Regular Grammar for IDENTIFIER
3. Original Finite Automaton for INTEGER CONSTANT
4. Converted Regular Grammar for INTEGER CONSTANT

## Key Functions

- `create_identifier_fa()` - Creates FA for identifier pattern
- `create_int_const_fa()` - Creates FA for integer constant pattern
- `fa_to_rg()` - Transforms FA to RG
- `print_fa()` - Displays FA structure
- `print_rg()` - Displays RG structure
