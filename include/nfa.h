#include <stdint.h>

#ifndef NFA_H 
#define NFA_H

typedef enum state_type {
  SINGLE,
  EPS_SINGLE,
  EPS_SPLIT,
  ACCEPT
} state_type;

typedef struct state  {

  char c;
  state_type type;

  struct state* out_left;
  struct state* out_right;

} state;

typedef struct frag {

  state* start;
  state** out;

} frag;


state* assemble_nfa(const char* regexp);

void destroy_nfa(state* nfa);

#endif
