#include "fa_rg.h"

// Helper functions
bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_underscore(char c) {
    return c == '_';
}

char classify_identifier(char c) {
    if (is_letter(c)) return 'l';
    if (is_digit(c)) return 'd';
    if (is_underscore(c)) return '_';
    return '\0';
}

char classify_int_const(char c) {
    if (c == '0') return '0';
    if (c == '-') return '-';
    if (c >= '1' && c <= '9') return 'd';
    return '\0';
}

// Acceptance: simulate DFA over the classified input
bool fa_accept(FiniteAutomaton* fa, const char* input, char (*classifier)(char)) {
    if (!fa || !input || !classifier) return false;

    int current = fa->start_state;
    for (const char *p = input; *p; ++p) {
        char sym = classifier(*p);
        if (sym == '\0') return false; // invalid symbol

        // find symbol index in alphabet
        int sym_idx = -1;
        for (int i = 0; i < fa->num_symbols; ++i) {
            if (fa->alphabet[i] == sym) { sym_idx = i; break; }
        }
        if (sym_idx == -1) return false;

        int next = fa->transitions[current][sym_idx];
        if (next == -1) return false; // no transition
        current = next;
    }

    // check if current is final
    for (int i = 0; i < fa->num_final_states; ++i) {
        if (fa->final_states[i] == current) return true;
    }
    return false;
}

// Print Finite Automaton
void print_fa(FiniteAutomaton* fa) {
    printf("FINITE AUTOMATON\n");
    printf("================\n");
    printf("States: {");
    for (int i = 0; i < fa->num_states; i++) {
        printf("q%d", fa->states[i]);
        if (i < fa->num_states - 1) printf(", ");
    }
    printf("}\n");
    
    printf("Start state: q%d\n", fa->start_state);
    
    printf("Final states: {");
    for (int i = 0; i < fa->num_final_states; i++) {
        printf("q%d", fa->final_states[i]);
        if (i < fa->num_final_states - 1) printf(", ");
    }
    printf("}\n");
    
    printf("Alphabet: {");
    for (int i = 0; i < fa->num_symbols; i++) {
        printf("%c", fa->alphabet[i]);
        if (i < fa->num_symbols - 1) printf(", ");
    }
    printf("}\n");
    
    printf("Transitions:\n");
    for (int i = 0; i < fa->num_states; i++) {
        for (int j = 0; j < fa->num_symbols; j++) {
            if (fa->transitions[i][j] != -1) {
                printf("  q%d --%c--> q%d\n", fa->states[i], fa->alphabet[j], fa->transitions[i][j]);
            }
        }
    }
}

// Print Regular Grammar
void print_rg(RegularGrammar* rg) {
    printf("REGULAR GRAMMAR\n");
    printf("===============\n");
    
    printf("Non-terminals: {");
    for (int i = 0; i < rg->num_nonterminals; i++) {
        printf("%c", rg->nonterminals[i]);
        if (i < rg->num_nonterminals - 1) printf(", ");
    }
    printf("}\n");
    
    printf("Terminals: {");
    for (int i = 0; i < rg->num_terminals; i++) {
        printf("%c", rg->terminals[i]);
        if (i < rg->num_terminals - 1) printf(", ");
    }
    printf("}\n");
    
    printf("Start symbol: %c\n", rg->start_symbol);
    
    printf("Production rules:\n");
    for (int i = 0; i < rg->num_rules; i++) {
        printf("  %d. %s\n", i + 1, rg->rules[i]);
    }
}

// Convert FA to RG
RegularGrammar fa_to_rg(FiniteAutomaton* fa) {
    RegularGrammar rg;
    
    // Initialize RG
    rg.num_nonterminals = fa->num_states;
    rg.num_terminals = fa->num_symbols;
    rg.num_rules = 0;
    
    // Copy non-terminals (states as q0, q1, etc.)
    for (int i = 0; i < fa->num_states; i++) {
        rg.nonterminals[i] = 'q' + fa->states[i];
    }
    
    // Copy terminals (alphabet)
    for (int i = 0; i < fa->num_symbols; i++) {
        rg.terminals[i] = fa->alphabet[i];
    }
    
    // Set start symbol
    rg.start_symbol = 'q' + fa->start_state;
    
    // Convert transitions to rules
    for (int i = 0; i < fa->num_states; i++) {
        for (int j = 0; j < fa->num_symbols; j++) {
            if (fa->transitions[i][j] != -1) {
                // Create rule: qi -> symbol qj
                snprintf(rg.rules[rg.num_rules], MAX_RULE_LEN, 
                        "q%d -> %c q%d", fa->states[i], fa->alphabet[j], fa->transitions[i][j]);
                rg.num_rules++;
            }
        }
    }
    
    // Add epsilon rules for final states
    for (int i = 0; i < fa->num_final_states; i++) {
        snprintf(rg.rules[rg.num_rules], MAX_RULE_LEN, 
                "q%d -> epsilon", fa->final_states[i]);
        rg.num_rules++;
    }
    
    return rg;
}
