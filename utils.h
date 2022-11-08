#ifndef H__UTILS
#define H__UTILS

#include <stdlib.h>

// Returns the word w's period
extern int word_period(const char *w);

// Returns the word w's edge
extern const char* word_edge(const char *w);

// Returns the "bon-prefixe" table of the word w
extern int* good_pref(const char *w, size_t len_w);

// Returns the "meilleur-prefixe" table of the word w
extern int* best_pref(const char *w, size_t len_w);

// Returns the "suffixe" table of the word w
extern int* suff(const char *w, size_t len_w);

// Returns the "good-suffixe" of a word w, which has been his
//  "suffixe" table calculated as suff
extern int* good_suff(size_t len_w, const int* suff);

// Returns the "dernière-occ" table of the word w : used in
//  Boyer-Moore algorithm
extern int* last_occ(const char *w, size_t len_w);

// Returns the "shift table" of the word w : used
//  in Horspool algorithm
extern int* shift_table(const char *w, size_t len_w);

// Returns the "shift table" of the word w : used
//  in Quick Search algorithm
extern int* qs_shift_table(const char *w, size_t len_w);


#endif