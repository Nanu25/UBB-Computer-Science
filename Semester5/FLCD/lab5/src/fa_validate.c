#include "fa_validate.h"

static bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool fa_accept_identifier(const char *s) {
    // FA: q0 --letter--> q1; q1 --letter|digit|_--> q1; final q1
    if (!s || !*s) return false;
    const char *p = s;
    if (!is_letter(*p)) return false; // q0 requires letter
    // now in q1
    for (++p; *p; ++p) {
        if (!(is_letter(*p) || is_digit(*p) || *p == '_')) return false;
    }
    return true; // q1 is final
}

bool fa_accept_int_const(const char *s) {
    if (!s || !*s) return false;
    const char *p = s;
    if (*p == '0') {
        return *(p + 1) == '\0'; // only "0" allowed
    }
    if (*p == '-') {
        ++p;
    }
    if (!(*p >= '1' && *p <= '9')) return false;
    for (++p; *p; ++p) {
        if (!is_digit(*p)) return false;
    }
    return true;
}


