#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "nfa.h"
#include "stack.h"

state match_state = {0, ACCEPT, NULL, NULL};

state* make_state(char c, state_type type, 
                  state* out_left, state* out_right) {
  
  state* s = malloc(sizeof(state));
  s->c = c;
  s->type = type;
  s->out_left = out_left;
  s->out_right = out_right;

  return s;
}

frag make_frag(state* start, state** out) {
  frag f = {start, out};
  return f;
}

state* assemble_nfa(const char* regexp) {

  return NULL;
}
