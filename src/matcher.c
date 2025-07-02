#include <stdbool.h>

#include "matcher.h"


// this does not deal with epsilon circles
//    - flag to see if we took other transitions than epsilons
bool match_nfa(const state* start, const char* input) {

  switch (start->type) {
    case EPS_SINGLE:
      return match_nfa(start->out_left, input);
    case SINGLE:
      if (*input && *input == start->c) {
        return match_nfa(start->out_left, input + 1);
      }

      return false;
    case EPS_SPLIT: 
      return match_nfa(start->out_right, input) || match_nfa(start->out_left, input);
    case ACCEPT:
      return *input == '\0' ? true : false;
    }
}

bool match(const char *regexp, const char *text) {






  return false;
}
