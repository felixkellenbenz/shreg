#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "nfa.h"
#include "stack.h"

static state match_state = {0, ACCEPT, NULL, NULL};
static state start_state = {0, EPS_SINGLE, NULL, NULL};
static frag start_frag = {&start_state, &start_state.out_left};

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

  size_t len = strlen(regexp);  
  state* s;
  frag expr_left = start_frag, expr_right;
  frag_stack stack = stack_init(1000);


  for (size_t i = 0; i < len; i++) {

    switch (regexp[i]) {

      case '|':

        break;
      case '*':

        break;
      default:
        s = make_state(regexp[i], SINGLE, NULL, NULL); 
         
        if (stack_size(&stack)) {
          stack_pop(&stack, &expr_left);
        }

        *expr_left.out = s;
         
        stack_push(&stack, make_frag(expr_left.start, &s->out_left));
        break;
    }
  }
  






  return NULL;
}
