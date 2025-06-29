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

// TODO: Handle cases where the stack is empty 
//       - validate regex before so stack is never empty
state* assemble_nfa(const char* regexp) {

  size_t len = strlen(regexp);  
  state* s;
  frag expr_left, expr_right;
  frag_stack stack = stack_init(1000);
  bool disjunction_flag = 0;

  stack_push(&stack, start_frag);

  for (size_t i = 0; i < len; i++) {

    switch (regexp[i]) {
      case '(': 
        s = make_state(0, EPS_SINGLE, NULL, NULL);
       
        stack_push(&stack, make_frag(s, &s->out_left)); 

        break;
      case ')':
        stack_pop(&stack, &expr_right);
        stack_pop(&stack, &expr_left); 

        if (!disjunction_flag) {
          *expr_left.out = expr_right.start;

          stack_push(&stack, make_frag(expr_left.start, expr_right.out));
        } else {
          frag before;
          stack_pop(&stack, &before);

          state* ending = make_state(0, EPS_SINGLE, NULL, NULL);         

          s = make_state(0, EPS_SPLIT, expr_left.start, expr_right.start);          

          *before.out = s;  
          *expr_left.out = ending;
          *expr_right.out = ending;

          stack_push(&stack, make_frag(before.start, &ending->out_left));
        }

        disjunction_flag = 0;
        break;
      case '|':
        s = make_state(0, EPS_SINGLE, NULL, NULL);
       
        stack_push(&stack, make_frag(s, &s->out_left)); 
        disjunction_flag = 1;

        break;
      case '*': 
        stack_pop(&stack, &expr_left);

        s = make_state(0, EPS_SPLIT, expr_left.start, NULL);
        *expr_left.out = s;

        stack_push(&stack, make_frag(s, &s->out_right));
        break;
      default:
        s = make_state(regexp[i], SINGLE, NULL, NULL); 
         
        stack_pop(&stack, &expr_left);

        *expr_left.out = s;
         
        stack_push(&stack, make_frag(expr_left.start, &s->out_left));
        break;
    }
  }

  stack_pop(&stack, &expr_left);
  *expr_left.out = &match_state;

  return expr_left.start;
}
