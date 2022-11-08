#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

int word_period(const char *w) {
    int wp = 0;
    int i = 0;
    size_t len = strlen(w);
    while ((size_t) i < len - 1) {
        int j;
        for (j = 0; j <= i; ++j) {
            if (w[j] != w[len - (size_t) i + (size_t) j - 1]) {
                break;
            }
        }
        if (j > i) {
            wp = i + 1;
        }
        ++i;

    }
    return (int) len - wp;
}


const char* word_edge(const char *w) {
    return w + strlen(w) - (size_t) word_period(w);
}


int* good_pref(const char *w, size_t len_w) {
    int* table = malloc((len_w + 1) * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for bon_pref table\n");
        return NULL;
    }
    table[0] = -1;
    int i = 0;
    for (size_t j = 1; j < len_w; ++j) {
        table[j] = i;
        while (i >= 0 && w[i] != w[j]) {
            i = table[i];
        }
        ++i;
    }
    table[len_w] = i;
    return table;
}


int* best_pref(const char *w, size_t len_w) {
    int* table = malloc((len_w + 1) * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for best_pref table\n");
        return NULL;
    }
    table[0] = -1;
    int i = 0;
    for (size_t j = 1; j < len_w; ++j) {
        if (w[i] == w[j]) {
            table[j] = table[i];
        } else {
            table[j] = i;
            do {
                i = table[i];
            } while (i >= 0 && w[i] != w[j]);
        }
        ++i;
    }
    table[len_w] = i;
    return table;
}


int* suff(const char *w, size_t len_w) {
    int* table = malloc((len_w + 1) * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for suff table\n");
        return NULL;
    }
    int g = (int) len_w - 1;
    int f = 0;
    for (int i = (int) len_w - 2; i >= 0; --i) {
        if (i > g && table[i + (int) len_w - 1 - f] != i - g) {
            if (i - g > table[i + (int) len_w - 1 - f]) {
                table[i] = table[i + (int) len_w - 1 - f];
            } else {
                table[i] = i - g;
            }
        } else {
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && w[g] == w[g + (int) len_w - 1 - f]) {
                --g;
            }
            table[i] = f - g;
        }
    } 
    return table;
}


int* good_suff(size_t len_w, const int* suff) {
    int* table = malloc((len_w + 1) * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for good_suff table\n");
        return NULL;
    }

    int i = 0;
    for (int j = (int) len_w - 2; j >= -1; --j) {
        if (j == -1 || suff[j] == j + 1) {
            while (i < (int) len_w - 1 - j) {
                table[i] = (int) len_w - 1 - j;
                ++i;
            }
        }
    }
    for (int j = 0; j < (int) len_w - 1; ++j) {
        table[(int) len_w - 1 - suff[j]] = (int) len_w - 1 - j;
    }
    return table;
}


int* last_occ(const char *w, size_t len_w) {
    int* table = malloc(UCHAR_MAX * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for last_occ table\n");
        return NULL;
    }

    for (int i = 0; i < UCHAR_MAX; ++i) {
        table[i] = (int) len_w;
    }

    for (int i = 0; i < (int) len_w - 1; ++i) {
        table[(int) w[i]] = (int) len_w - 1 - i;
    }
    return table;
}


int* shift_table(const char *w, size_t len_w) {
    int* table = malloc(UCHAR_MAX * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for shift table\n");
        return NULL;
    }

    for (int i = 0; i < UCHAR_MAX; ++i) {
        table[i] = (int) len_w;
    }
    for (int i = 0; i < (int) len_w - 1; ++i) {
        table[(int) w[i]] = (int) len_w - i - 1;
    }
    return table;
}


int* qs_shift_table(const char *w, size_t len_w) {
    int* table = malloc(UCHAR_MAX * sizeof(int));
    if (!table) {
        fprintf(stderr, "Cannot allocate memory for quicksearch shift table\n");
        return NULL;
    }

    for (int i = 0; i < UCHAR_MAX; ++i) {
        table[i] = (int) len_w + 1;
    }
    for (int i = 0; i < (int) len_w; ++i) {
        table[(int) w[i]] = (int) len_w - i;
    }
    return table;
}