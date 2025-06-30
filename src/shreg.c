#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nfa.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const char* preprocess(const char* s);

int main(int argc, char** argv) {

  if (argc < 3) {
    printf(ANSI_COLOR_RED "usage error:" ANSI_COLOR_RESET);
    printf(" please provide a regex and a string\n");
  }  

  const char* regexp = preprocess(argv[1]);
  const char* input = argv[2];
  state* nfa = assemble_nfa(regexp);


  free(regexp);
  destroy_nfa(nfa);
}

const char* preprocess(const char* s) {

  if(s[strlen(s) - 1] == ')' && s[0] == '(') {
    char* dyn_alloc = malloc(strlen(s) + 1);
    dyn_alloc[strlen(s)] = 0; 
    strcpy(dyn_alloc, s);
    return dyn_alloc; 
  }

  char* padded = malloc(strlen(s) + 3);

  strcpy(padded + 1, s);
  padded[0] = '(';
  padded[strlen(s) + 1] = ')';
  padded[strlen(s) + 2] = 0;

  return padded;
}
