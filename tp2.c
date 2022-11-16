// A PRIORI ON EN AURA PAS BESOIN MAIS JE L'AI MIT AU CAS OU

#include "tp2.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int slow_naive_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    for (size_t i = 0; i < len_s; ++i) {
        size_t j;
        for (j = 0; j < len_w; ++j) {
            if (i + j >= len_s  - 1 || w[j] != s[i + j]) {
                break;
            }
        }
        if (j == len_w) {
            ++cpt;
        }
    }
    return cpt;
}


int fast_naive_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    for (size_t i = 0; i < len_s; ++i) {
        size_t j = 0;
        if (w[j] != s[i]) {
            continue;
        }
        for (j = 1; j < len_w; ++j) {
            if (i + j >= len_s  - 1 || w[j] != s[i + j]) {
                break;
            }
        }
        if (j == len_w) {
            ++cpt;
        }
    }
    return cpt;
}


int fast_naive_sentinel_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    char ss[len_w + len_s + 1];
    memcpy(ss, s, len_s);
    memcpy(ss + len_s, w, len_w);
    ss[len_w + len_s] = '\0';
    for (size_t i = 0; i < len_s + len_w; ++i) {
        size_t j = 0;
        if (w[j] != ss[i]) {
            continue;
        }
        for (j = 1; j < len_w; ++j) {
            if (i + j >= len_s + len_w || w[j] != ss[i + j]) {
                break;
            }
        }
        if (j == len_w && j + i < len_w + len_s) {
            ++cpt;
        }
    }
    return cpt;
}


int slow_naive_str_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    for (size_t i = 0; i < len_s - len_w; ++i) {
        if (strncmp(s + i, w, strlen(w)) == 0) {
            ++cpt;
        }
        
    }

    return cpt;
}


int fast_naive_str_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    for (size_t i = 0; i < len_s - len_w; ++i) {
        size_t j = 0;
        if (w[j] != s[i]) {
            continue;
        }
        if (strncmp(s + i + 1, w + 1, strlen(w) - 1) == 0) {
            ++cpt;
        }
    }
    return cpt;
}


int fast_naive_str_sentinel_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_s = strlen(s);
    size_t len_w = strlen(w);
    char ss[len_w + len_s + 1];
    memcpy(ss, s, len_s);
    memcpy(ss + len_s, w, len_w);
    ss[len_w + len_s] = '\0';
    for (size_t i = 0; i < len_s; ++i) {
        size_t j = 0;
        if (w[j] != ss[i]) {
            continue;
        }
        if (j + i < len_w + len_s && strncmp(s + i + 1, w + 1, strlen(w) - 1) == 0) {
            ++cpt;
        }
    }
    return cpt;
}


int mp_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_w = strlen(w);
    size_t len_s = strlen(s);
    int* table = good_pref(w, len_w);

    int i = 0;
    for (size_t j = 0; j < len_s; ++j) {
        while (i >= 0 && w[i] != s[j]) {
            i = table[i];
        }
        ++i;
        if ((size_t) i == len_w) {
            ++cpt;
            i = table[i];
        }
    }
    free(table);
    return cpt;
}


int kmp_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_w = strlen(w);
    size_t len_s = strlen(s);
    int* table = best_pref(w, len_w);

    int i = 0;
    for (size_t j = 0; j < len_s; ++j) {
        while (i >= 0 && w[i] != s[j]) {
            i = table[i];
        }
        ++i;
        if ((size_t) i == len_w) {
            ++cpt;
            i = table[i];
        }
    }
    free(table);
    return cpt;
}


int bm_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_w = strlen(w);
    size_t len_s = strlen(s);
    int* sufft = suff(w, len_w);
    int* table = good_suff(len_w, sufft);
    int *ltoc = last_occ(w, len_w);
    int j = (int) len_w - 1;
    int i = 0;
    while (j < (int) len_s) {
        i = (int) len_w - 1;
        while (i >= 0 && w[i] == s[j - (int) len_w + 1 + i]) {
            --i;
        }
        if (i < 0) {
            ++cpt;
            j += table[0];
        } else {
            if (table[i] > ltoc[(int) s[j - (int) len_w + 1 + i]] - (int) len_w + 1 + i) {
                j += table[i];
            } else {
                j += ltoc[(int) s[j - (int) len_w + 1 + i]] - (int) len_w + 1 + i; 
            }
        }
    }
    free(ltoc);
    free(sufft);
    free(table);
    return cpt;
}


int horspool_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_w = strlen(w);
    size_t len_s = strlen(s);
    int *stable = shift_table(w, len_w);
    int i = 0;
    int diff = (int) (len_s - len_w);
    while (i < diff) {
        if (s[i + (int) len_w - 1] == w[len_w - 1]) {
            if (memcmp(s + i, w, len_w - 1) == 0) {
                ++cpt;
            }
        }
        i += stable[(int) s[i + (int) len_w - 1]];
    }
    free(stable);
    return cpt;
}


int qs_search(const char *w, const char *s) {
    int cpt = 0;
    size_t len_w = strlen(w);
    size_t len_s = strlen(s);
    int *stable = qs_shift_table(w, len_w);
    int i = 0;
    int diff = (int) (len_s - len_w);
    while (i < diff) {
        if (memcmp(w, s + i, len_w) == 0) {
            ++cpt;
        }
        i += stable[(int) s[i + (int) len_w]];
    }
    free(stable);
    return cpt;
}

