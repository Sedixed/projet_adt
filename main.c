#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"

int main(void) {
    const char *s = (const char *)"ataataatataatataa";
    const char *w = (const char *)"ataatata";
    printf("%d occurrences de %s dans %s via slow_naive_search\n", slow_naive_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via fast_naive_search\n", fast_naive_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via fast_naive_sentinel_search\n", fast_naive_sentinel_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via slow_naive_str_search\n", slow_naive_str_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via fast_naive_str_search\n", fast_naive_str_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via fast_naive_str_sentinel_search\n", fast_naive_str_sentinel_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via mp_search\n", mp_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via kmp_search\n", kmp_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via bm_search\n", bm_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via horspool_search\n", horspool_search(w, s), w, s);
    printf("%d occurrences de %s dans %s via qs_search\n", qs_search(w, s), w, s);
    return 0;
}