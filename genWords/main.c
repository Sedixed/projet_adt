#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "generate_words.h"

#define REQUIRED_ARGUMENTS 4

int main(int argc, char const *argv[]) {
  if (argc < REQUIRED_ARGUMENTS + 1) {
    fprintf(stderr, "Usage : %s <nbWords> <minWordLength> <maxWordLength> <alphabetSize>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int nb_words;
  if (sscanf(argv[1], "%d", &nb_words) != 1 || nb_words <= 0) {
		fprintf(stderr, "Error : number of words must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}

  int min_len;
  if (sscanf(argv[2], "%d", &min_len) != 1 || min_len <= 0) {
		fprintf(stderr, "Error : minimum word length must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}

  int max_len;
  if (sscanf(argv[3], "%d", &max_len) != 1 || max_len <= 0) {
		fprintf(stderr, "Error : maximum word length must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}

  if (max_len < min_len) {
    fprintf(stderr, "Error : maximum word length must be greater or equal than minimum word length.\n");
		exit(EXIT_FAILURE);
  }

  int alphabet_size;
  if (sscanf(argv[4], "%d", &alphabet_size) != 1 || alphabet_size <= 0) {
		fprintf(stderr, "Error : alphabet size must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}
  
  srand((unsigned) time(NULL));
  generate_words(nb_words, min_len, max_len, alphabet_size);
  return EXIT_SUCCESS;
}