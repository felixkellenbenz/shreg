#include <stddef.h>
#include <stdlib.h>

#include "stack.h"

frag_stack stack_init(size_t stack_size) { 
  frag* elems = malloc(sizeof(frag) * stack_size);
  frag_stack stack = {0, stack_size, elems};
  return stack; 
}

void stack_delete(frag_stack* stack) {
  free(stack->elems);
}

void stack_push(frag_stack* stack, frag elem) {

  if (stack->idx >= stack->size) {
    return;
  }

  stack->elems[stack->idx++] = elem;
}

int stack_pop(frag_stack* stack, frag* out) {

  if (!out || !stack->idx) {
    return 0;
  }

  *out = stack->elems[stack->idx];
  return 1;
}
