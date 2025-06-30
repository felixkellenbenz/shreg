#ifndef MATCHER_H
#define MATCHER_H

#include <stdbool.h>

#include "nfa.h"

/*
 * A regular expression e is considered valid iff:
 *    - e = c             c for any character c 
 *    - e = (exp1)*       where exp1 is another valid regular expression
 *    - e = exp1exp2      where exp1 and exp2 are valid regular expressions
 *    - e = (exp1 | exp2) where exp1 and exp2 are valid regular expressions
 *
 * More advanced:
 *    - e = [...]         where ... ist a set of characters
 *    - e = .             . can be any character 
 *    - e = (exp1)+       where exp1 is another valid regular expression
 *    - e = exp1?         where exp1 is another valid ragular expression
 * */


bool match_nfa(const state* start, const char* input);

bool match(const char* regexp, const char* text);












#endif
