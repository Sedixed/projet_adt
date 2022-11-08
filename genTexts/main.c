#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "generate_text.h"

#define REQUIRED_ARGUMENTS 2

int main(int argc, char const *argv[]) {
  if (argc < REQUIRED_ARGUMENTS + 1) {
    fprintf(stderr, "Usage : %s <textSize> <alphabetSize>.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int text_size;
  if (sscanf(argv[1], "%d", &text_size) != 1 || text_size <= 0) {
		fprintf(stderr, "Error : text size must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}

  int alphabet_size;
  if (sscanf(argv[2], "%d", &alphabet_size) != 1 || alphabet_size <= 0) {
		fprintf(stderr, "Error : alphabet size must be a strictly positive integer.\n");
		exit(EXIT_FAILURE);
	}
	
	srand((unsigned) time(NULL));
  generate_text(alphabet_size, text_size);
  return EXIT_SUCCESS;
}
