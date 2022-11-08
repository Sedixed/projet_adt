#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "generate_text.h"

#define FIRST_CHAR '!'

void generate_text(int alphabet_size, int text_size) {
  for (int i = 0; i < text_size; ++i) {
    int c = (rand() % alphabet_size + FIRST_CHAR);
    fprintf(stdout, "%c", c);
  }
}
