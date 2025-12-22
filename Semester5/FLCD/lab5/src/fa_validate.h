#ifndef FA_VALIDATE_H
#define FA_VALIDATE_H

#include <stdbool.h>

// FA-based validators integrated into the scanner
// Returns true if the input matches the IDENTIFIER FA
bool fa_accept_identifier(const char *input);

// Returns true if the input matches the INTEGER CONSTANT FA
// Rules: 0 | [-]?[1-9][0-9]*
bool fa_accept_int_const(const char *input);

#endif // FA_VALIDATE_H


