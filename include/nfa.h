#ifndef NFA_H 
#define NFA_H

#include <stdbool.h>
#include <stdint.h>

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

  // this is for checking if a state was already visited 
  // when adding them to the free queue
  // this should not be part of the state itself
  bool visited;

} state;

typedef struct frag {

  state* start;
  state** out;

} frag;


state* assemble_nfa(const char* regexp);

void destroy_nfa(state* nfa);

#endif
