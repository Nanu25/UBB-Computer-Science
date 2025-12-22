#ifndef FA_RG_H
#define FA_RG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 50
#define MAX_RULES 100
#define MAX_RULE_LEN 50

// Finite Automaton structure
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

// Regular Grammar structure
typedef struct {
    char nonterminals[MAX_SYMBOLS];   // Non-terminal symbols
    int num_nonterminals;             // Number of non-terminals
    char terminals[MAX_SYMBOLS];      // Terminal symbols
    int num_terminals;                // Number of terminals
    char start_symbol;                // Start symbol
    char rules[MAX_RULES][MAX_RULE_LEN]; // Production rules
    int num_rules;                    // Number of rules
} RegularGrammar;

// Function declarations
void print_fa(FiniteAutomaton* fa);
void print_rg(RegularGrammar* rg);
RegularGrammar fa_to_rg(FiniteAutomaton* fa);
bool is_letter(char c);
bool is_digit(char c);
bool is_underscore(char c);

// Acceptance: checks if input is accepted by FA using a classifier
// classifier: maps input char -> symbol from fa->alphabet, or '\0' if invalid
bool fa_accept(FiniteAutomaton* fa, const char* input, char (*classifier)(char));

// Symbol classifiers for our demos
char classify_identifier(char c);   // returns 'l', 'd', '_' or '\0'
char classify_int_const(char c);    // returns 'd', '0', '-' or '\0'

#endif
