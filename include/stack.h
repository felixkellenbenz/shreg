#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>

#include "nfa.h"

typedef struct frag_stack {

  size_t idx;
  size_t size;
  frag* elems;  
  
} frag_stack;

frag_stack stack_init(size_t stack_size);

void stack_delete(frag_stack* stack);

void stack_push(frag_stack* stack, frag elem);

int stack_pop(frag_stack* stack, frag* out);

#endif
