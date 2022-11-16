// A PRIORI ON EN AURA PAS BESOIN MAIS JE L'AI MIT AU CAS OU


#ifndef H__TRIE
#define H__TRIE

#define WORD_END '\0'

// Returns the number of occurences of w in s using the naive search algorithm without
//  fast loop and using internal loop
extern int slow_naive_search(const char *w, const char *s);


// Returns the number of occurences of w in s using the naive search algorithm with
//  fast loop and using internal loop
extern int fast_naive_search(const char *w, const char *s);


// Returns the number of occurences of w in s using the naive search algorithm with
//  fast loop, using internal loop and a sentinel
extern int fast_naive_sentinel_search(const char *w, const char *s);


// Returns the number of occurences of w in s using the naive search algorithm without
//  fast loop and using strncmp
extern int slow_naive_str_search(const char *w, const char *s);


// Returns the number of occurences of w in s using the naive search algorithm with
//  fast loop and using strncmp
extern int fast_naive_str_search(const char *w, const char *s);


// Returns the number of occurences of w in s using the naive search algorithm with
//  fast loop and using strncmp and a sentinel
extern int fast_naive_str_sentinel_search(const char *w, const char *s);

// Returns the number of occurences of w in s using the Morris-Pratt algorithm
extern int mp_search(const char *w, const char *s);

// Returns the number of occurences of w in s using the Knuth-Morris-Pratt algorithm
extern int kmp_search(const char *w, const char *s);

// Returns the number of occurences of w in s using the Boyer-Moore algorithm
extern int bm_search(const char *w, const char *s);

// Returns the number of occurences of w in s using the Horspool algorithm
extern int horspool_search(const char *w, const char *s);

// Returns the number of occurences of w in s using the Quick Search algorithm
extern int qs_search(const char *w, const char *s);

#endif