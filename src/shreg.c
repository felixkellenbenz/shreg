#include <stdio.h>

#include "nfa.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char** argv) {

  assemble_nfa("aaaaa");

  if (argc < 2) {
    printf(ANSI_COLOR_RED "usage error:" ANSI_COLOR_RESET);
    printf(" please provide a regex and a string");
  }  

}
