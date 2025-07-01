#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "nfa.h"
#include "stack.h"

static state match_state = {0, ACCEPT,NULL, NULL, false};
static state start_state = {0, EPS_SINGLE, NULL, NULL, false};
static frag start_frag = {&start_state, &start_state.out_left};
static size_t number_states = 2;

static state* make_state(char c, state_type type, 
                  state* out_left, state* out_right) {
  
  state* s = malloc(sizeof(state));
  s->c = c;
  s->type = type;
  s->out_left = out_left;
  s->out_right = out_right;
  s->visited = false;
  number_states++;

  return s;
}

static frag make_frag(state* start, state** out) {
  frag f = {start, out};
  return f;
}

static inline char lookahead_one(const char* regexp, size_t len, size_t idx) {
  return idx + 1 < len ? regexp[idx + 1] : 0;
}

static size_t count_levels(const char* regexp) {
  
  size_t max_level = 0, counter = 0;
 
  for (size_t i = 0; i < strlen(regexp); i++) {
    if (regexp[i] == '(') {
      counter++;
    }

    if (regexp[i] == ')') {
      max_level = counter > max_level ? counter : max_level;
      counter--;
    }
  }
  
  return max_level;
}

static void concatenate(frag_stack* stack, char lookahead) {
  frag expr_left, expr_right;
   
  if (lookahead == '*') {
    return;
  }

  stack_pop(stack, &expr_right);
  stack_pop(stack, &expr_left);
  
  *expr_left.out = expr_right.start;

  stack_push(stack, make_frag(expr_left.start, expr_right.out));
}

static void handle_closing_paren(frag_stack* stack, bool disjunction_flag, char lookahead) {
  frag expr_left, expr_right;
  state* s;

  if (disjunction_flag) {
    stack_pop(stack, &expr_right);
    stack_pop(stack, &expr_left);

    s = make_state(0, EPS_SPLIT, expr_right.start, expr_left.start);
    state* ending = make_state(0, EPS_SINGLE, NULL, NULL);

    *expr_left.out = ending;
    *expr_right.out = ending;
  
    stack_push(stack, make_frag(s,  &ending->out_left));
  }

  concatenate(stack, lookahead); 
}

// TODO: Handle cases where the stack is empty 
//       - validate regex before, so stack is never empty

// This method expects a valid regex
state* assemble_nfa(const char* regexp) {

  size_t len = strlen(regexp);  
  state* s;
  frag expr_left, expr_right;
  frag_stack stack = stack_init(1000);
  bool* disjunction_flags = malloc(sizeof(bool) * count_levels(regexp));
  memset(disjunction_flags, 0, count_levels(regexp) * sizeof(bool));

  stack_push(&stack, start_frag);

  size_t current_level = 0;
  for (size_t i = 0; i < len; i++) {

    switch (regexp[i]) {
      case '(': 
        current_level++;
        s = make_state(0, EPS_SINGLE, NULL, NULL); 

        stack_push(&stack, make_frag(s, &s->out_left)); 
        break;
      case ')':
        handle_closing_paren(&stack, disjunction_flags[current_level],
                             lookahead_one(regexp, len, i));

        disjunction_flags[current_level--] = 0;
        break;
      case '|':
        s = make_state(0, EPS_SINGLE, NULL, NULL);
       
        stack_push(&stack, make_frag(s, &s->out_left)); 
        disjunction_flags[current_level] = 1;
        break;
      case '*': 
        stack_pop(&stack, &expr_right);
        stack_pop(&stack, &expr_left);

        s = make_state(0, EPS_SPLIT, expr_right.start, NULL);

        *expr_right.out = s;
        *expr_left.out = s;

        stack_push(&stack, make_frag(expr_left.start, &s->out_right));
        break;
      default:
        s = make_state(regexp[i], SINGLE, NULL, NULL);   
        stack_push(&stack, make_frag(s, &s->out_left));

        concatenate(&stack, lookahead_one(regexp, len, i)); 
        break;
    }
  }

  stack_pop(&stack, &expr_left);
  *expr_left.out = &match_state;

  free(disjunction_flags);

  return expr_left.start;
}

void destroy_nfa(state* nfa) { 

  state** all_states = malloc(number_states * sizeof(state*));   
  size_t insert_idx = 1, take_index = 0; 
  all_states[0] = nfa;
  state* current = nfa;

  while (current->out_left || current->out_right) {
    current = all_states[take_index++];

    if (current->out_left && !current->out_left->visited) {
      current->out_left->visited = true;
      all_states[insert_idx++] = current->out_left;
    } 

    if (current->out_right && !current->out_right->visited) {
      current->out_right->visited = true;
      all_states[insert_idx++] =  current->out_right;
    }
  }

  for (size_t i = 0; i < number_states; i++) {
    // only start and match state are allocated statically
    if (all_states[i] == &start_state || all_states[i] == &match_state) {
      continue;
    }

    free(all_states[i]);
  }

  free(all_states);
}
