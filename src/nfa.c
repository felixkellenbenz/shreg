#include <stdlib.h>

#include "nfa.h"

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

frag make_frag(state* start, state* out) {
  frag f = {start, out};
  return f;
}

state* assemble_nfa(const char* regexp) {
 
  if (!regexp) {
    return NULL;
  }

  frag stack[1000], *stackp, expr; 
  
  state* s;
  const char* iter = regexp;

  #define push(s)  *stackp++ = s
  #define pop()    *--stackp 
  
  for (; *iter; iter++) {
      
    switch(*iter) {

      case '|':
        

        break;
      case '*':
        expr = pop();
        s = make_state(0, SPLIT, expr.start, NULL);
        expr.out = s; 
        push(make_frag(s, s->out_right)); 
        break;
      default:
        s = make_state(*iter, SINGLE, NULL, NULL);   
        push(make_frag(s, s->out_left)); 
        break;
    }
  }

  



  return NULL;
}

