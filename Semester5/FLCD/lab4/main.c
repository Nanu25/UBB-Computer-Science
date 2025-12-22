#include "fa_rg.h"

// Create the IDENTIFIER Finite Automaton
FiniteAutomaton create_identifier_fa() {
    FiniteAutomaton fa;
    
    // Initialize
    fa.num_states = 2;
    fa.states[0] = 0;  // q0
    fa.states[1] = 1;  // q1
    
    fa.start_state = 0;  // q0
    
    fa.num_final_states = 1;
    fa.final_states[0] = 1;  // q1
    
    // Alphabet: letter, digit, underscore
    fa.num_symbols = 3;
    fa.alphabet[0] = 'l';  // letter
    fa.alphabet[1] = 'd';  // digit
    fa.alphabet[2] = '_';  // underscore
    
    // Initialize transition table to -1 (no transition)
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            fa.transitions[i][j] = -1;
        }
    }
    
    // Define transitions
    // q0 --letter--> q1
    fa.transitions[0][0] = 1;
    
    // q1 --letter--> q1
    fa.transitions[1][0] = 1;
    
    // q1 --digit--> q1
    fa.transitions[1][1] = 1;
    
    // q1 --underscore--> q1
    fa.transitions[1][2] = 1;
    
    return fa;
}

// Create the INTEGER CONSTANT Finite Automaton
FiniteAutomaton create_int_const_fa() {
    FiniteAutomaton fa;
    
    // Initialize
    fa.num_states = 3;
    fa.states[0] = 0;  // q0
    fa.states[1] = 1;  // q1
    fa.states[2] = 2;  // q2
    
    fa.start_state = 0;  // q0
    
    fa.num_final_states = 2;
    fa.final_states[0] = 1;  // q1 (for "0")
    fa.final_states[1] = 2;  // q2 (for other numbers)
    
    // Alphabet: digit, minus, zero
    fa.num_symbols = 3;
    fa.alphabet[0] = 'd';  // digit (1-9)
    fa.alphabet[1] = '-';  // minus
    fa.alphabet[2] = '0';  // zero
    
    // Initialize transition table
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            fa.transitions[i][j] = -1;
        }
    }
    
    // Define transitions
    // q0 --0--> q1 (for "0")
    fa.transitions[0][2] = 1;
    
    // q0 --minus--> q2 (for negative numbers)
    fa.transitions[0][1] = 2;
    
    // q0 --digit--> q2 (for positive numbers)
    fa.transitions[0][0] = 2;
    
    // q2 --digit--> q2 (more digits)
    fa.transitions[2][0] = 2;
    
    return fa;
}

int main() {
    printf("========================================\n");
    printf("FA to RG Transformation Demo\n");
    printf("========================================\n\n");
    
    // Demo 1: IDENTIFIER
    printf("DEMO 1: IDENTIFIER PATTERN\n");
    printf("==========================\n\n");
    
    FiniteAutomaton identifier_fa = create_identifier_fa();
    printf("Original Finite Automaton:\n");
    print_fa(&identifier_fa);
    printf("\n");
    
    RegularGrammar identifier_rg = fa_to_rg(&identifier_fa);
    printf("Converted Regular Grammar:\n");
    print_rg(&identifier_rg);
    printf("\n");
    
    // Acceptance tests for IDENTIFIER
    const char* id_tests[] = { "a", "variable1", "_bad", "1x", "a_b", "A1_", NULL };
    printf("Identifier acceptance tests:\n");
    for (int i = 0; id_tests[i]; ++i) {
        bool ok = fa_accept(&identifier_fa, id_tests[i], classify_identifier);
        printf("  %-12s -> %s\n", id_tests[i], ok ? "ACCEPT" : "REJECT");
    }
    printf("\n");

    // Demo 2: INTEGER CONSTANT
    printf("DEMO 2: INTEGER CONSTANT PATTERN\n");
    printf("=================================\n\n");
    
    FiniteAutomaton int_fa = create_int_const_fa();
    printf("Original Finite Automaton:\n");
    print_fa(&int_fa);
    printf("\n");
    
    RegularGrammar int_rg = fa_to_rg(&int_fa);
    printf("Converted Regular Grammar:\n");
    print_rg(&int_rg);
    printf("\n");
    
    // Acceptance tests for INTEGER CONSTANT
    const char* int_tests[] = { "0", "5", "123", "-42", "-0", "00", "-", "a1", NULL };
    printf("Integer constant acceptance tests:\n");
    for (int i = 0; int_tests[i]; ++i) {
        bool ok = fa_accept(&int_fa, int_tests[i], classify_int_const);
        printf("  %-6s -> %s\n", int_tests[i], ok ? "ACCEPT" : "REJECT");
    }
    printf("\n");

    printf("========================================\n");
    printf("Transformation Complete!\n");
    printf("========================================\n");
    
    return 0;
}
