#include <stdio.h>
#include <stdlib.h>
#include "generate_words.h"

#define FIRST_CHAR '!'

void generate_words(int nb_words, int min_len, int max_len, int alphabet_size) {
  for (int i = 0; i < nb_words; ++i) {
    int len = (rand() % (max_len - min_len + 1)) + min_len;
    for (int j = 0; j < len; ++j) {
      int c = (rand() % alphabet_size + FIRST_CHAR);
      fprintf(stdout, "%c", c);
    }
    fprintf(stdout, "\n");
  }
}