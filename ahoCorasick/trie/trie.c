#include "trie.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_TRANS -1


// --- Fonctions auxiliaires ---

// Calcule la longueur du mot w jusqu'au caractère e (supposé présent) et la renvoie.
int wordLength(unsigned char *w, unsigned char e);

// On utilise les matrices de transitions
#if USE_HASH == 0

struct _trie {
  int maxNode;      /* Nombre maximal de noeuds du trie */
  int nextNode;     /* Indice du prochain noeud disponible */
  int **transition; /* matrice de transition */
  char *finite;     /* etats terminaux */
};

Trie createTrie(int maxNode) {
  if (maxNode < 0) {
    fprintf(stderr, "Taille de trie invalide (négative)\n");
    return NULL;
  }

  Trie t = malloc(sizeof(*t));
  if (t == NULL) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    return NULL;
  }

  t->maxNode = maxNode;
  t->nextNode = 1;
  t->transition = malloc(((size_t)maxNode) * sizeof(*(t->transition)));
  if (!(t->transition)) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    free(t);
    return NULL;
  }

  int i = 0;
  for (; i < maxNode; ++i) {
    t->transition[i] = malloc(UCHAR_MAX * sizeof(int));
    if (!(t->transition[i])) {
      fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
      for (int k = 0; k < i; ++k) {
        free(t->transition[k]);
      }
      free(t);
      return NULL;
    }
    for (int k = 0; k < UCHAR_MAX; ++k) {
      t->transition[i][k] = NO_TRANS;
    }
  }

  t->finite = calloc(((size_t)maxNode), sizeof(*(t->finite)));
  if (!(t->finite)) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    for (int k = 0; k < i; ++k) {
      free(t->transition[k]);
    }
    free(t->transition);
    free(t);
    return NULL;
  }

  return t;
}

int isInTrie(Trie trie, unsigned char *w) {
  if (!trie) {
    fprintf(stderr, "Trie invalide\n");
    return 0;
  }

  if (!w) {
    fprintf(stderr, "Mot invalide\n");
    return 0;
  }

  unsigned char *p = w;
  int i = 0;
  while (*p != END_INDICATOR) {
    int j = trie->transition[i][*p];
    if (j == NO_TRANS) {
      return 0;
    }
    i = j;
    ++p;
  }

  return trie->finite[i];
}

void insertInTrie(Trie trie, unsigned char *w) {
  if (!trie) {
    fprintf(stderr, "Trie invalide\n");
    return;
  }

  if (!w) {
    fprintf(stderr, "Mot invalide\n");
    return;
  }

  // 1ere partie : Trouver à partir d'où écrire (préfixe commun déjà stocké)
  unsigned char *p = w;
  int i = 0;
  int j = trie->transition[i][*p];
  while (*p != END_INDICATOR && j != NO_TRANS) {
    i = j;
    ++p;
    j = trie->transition[i][*p];
  }
  if (*p == END_INDICATOR) {
    trie->finite[i] = 1;
    return;
  }
  if (wordLength(p, END_INDICATOR) > trie->maxNode - trie->nextNode + 1) {
    fprintf(stderr, "espace insuffisant (wl = %d, nextNode = %d, maxNode = %d)\n", wordLength(p, END_INDICATOR), trie->nextNode, trie->maxNode);
    return;
  }

  j = trie->nextNode;
  while (*p != END_INDICATOR) {
    trie->transition[i][*p] = j;
    i = j;
    j -= -1;
    ++p;
    ++trie->nextNode;
  }
  trie->finite[i] = 1;
}

void disposeTrie(Trie *trie) {
  if (!(*trie)) {
  }
  for (int k = 0; k < (*trie)->maxNode; ++k) {
    free((*trie)->transition[k]);
  }
  free((*trie)->transition);
  free((*trie)->finite);
  free((*trie));
  *trie = NULL;
}

// On utilise les tables de hachage
#else

/**
 * Pour n transitions, le tableau de la table de hachage doit
 * contenir n * RELATIVE_CAPACITY éléments.
 */
#define RELATIVE_CAPACITY 0.75

struct _list {
  int startNode; /* etat de depart de la transition */
  int targetNode; /* cible de la transition */
  unsigned char letter; /* etiquette de la transition */
  struct _list *next; /* maillon suivant */
};

typedef struct _list *List;

struct _trie {
  int maxNode; /* Nombre maximal de noeuds du trie */
  int nextNode; /* Indice du prochain noeud disponible */
  List *transition; /* listes d’adjacence */
  int arrSize; /* Taille du tableau */
  char *finite; /* etats terminaux */
};

// Update plus tard
int hash(Trie t, int node, unsigned char c) {
	
  return (31 * node * 53 * (int) c) % t->arrSize;
}

Trie createTrie(int maxNode) {
  if (maxNode < 0) {
    fprintf(stderr, "Taille de trie invalide (négative)\n");
    return NULL;
  }

  Trie t = malloc(sizeof(*t));
  if (t == NULL) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    return NULL;
  }

  t->maxNode = maxNode;
  t->nextNode = 1;
  t->arrSize = (int) ((t->maxNode) * RELATIVE_CAPACITY);
  t->transition = calloc((size_t) t->arrSize, sizeof(*(t->transition)));
  if (!(t->transition)) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    free(t);
    return NULL;
  }

  t->finite = calloc((size_t) maxNode, sizeof(*(t->finite)));
  if (!(t->finite)) {
    fprintf(stderr, "Erreur lors de l'allocation d'un trie\n");
    free(t->transition);
    free(t);
    return NULL;
  }

  return t;
}

int isInTrie(Trie trie, unsigned char *w) {
  if (!trie) {
    fprintf(stderr, "Trie invalide\n");
    return 0;
  }

  if (!w) {
    fprintf(stderr, "Mot invalide\n");
    return 0;
  }

  unsigned char *p = w;
  int i = 0;
  int first = 1;
  while (*p != END_INDICATOR) {
    int h = hash(trie, i, *p);
    if (trie->transition[h] == NULL) {
      return 0;
    }
    List li = trie->transition[h];
    while (li != NULL && li->letter != *p) {
      li = li->next;
    }
    if (!li) {
			return 0;
		}
		// Test pour savoir si c'est la première transition
		if (first == 1) {
			if (li->startNode != 0) {
				return 0;
			}
			first = -1;
		}

    i = li->targetNode;
    ++p;
  }

  return trie->finite[i];
}


void insertInTrie(Trie trie, unsigned char *w) {
  if (!trie) {
    fprintf(stderr, "Trie invalide\n");
    return;
  }

  if (!w) {
    fprintf(stderr, "Mot invalide\n");
    return;
  }

  unsigned char *p = w;
  int i = 0;
  while (*p != END_INDICATOR) {
    int h = hash(trie, i, *p);

    // Recherche d'un potentiel préfixe
    List li = trie->transition[h];
    // Liste non vide
    if (li != NULL) {
      // Recherche du caractère dans la liste 
      while (li->letter != *p) {
        if (li->next == NULL) {
          break;
        }
        li = li->next;
      }
      // Caractère trouvé
      if (li->letter == *p) {
        i = li->targetNode;
        ++p;
        continue;
      }
    }

    if (wordLength(p, END_INDICATOR) > trie->maxNode - trie->nextNode + 1) {
      fprintf(stderr, "espace insuffisant (wl = %d, nextNode = %d, maxNode = %d)\n", wordLength(p, END_INDICATOR), trie->nextNode, trie->maxNode);
      return;
    }

    List new = malloc(sizeof(&new));
    if (!new) {
      fprintf(stderr, "Erreur lors de l'allocation d'une liste\n");
      return;
    }
    new->letter = *p;
    new->startNode = i;
    new->targetNode = trie->nextNode++;
    new->next = NULL;
    i = new->targetNode;
    if (li == NULL) {
      trie->transition[h] = new;
    } else {
      li->next = new;
    }
    ++p;
    
  }
  trie->finite[i] = 1;
}


void disposeTrie(Trie *trie) {
  if (!(*trie)) {
  }

  for (int k = 0; k < (*trie)->arrSize; ++k) {
    if (!(*trie)->transition[k]) {
      continue;
    }
    List li = (*trie)->transition[k];
    while (li->next != NULL) {
      List libis = li;
      li = li->next;
      free(libis);
    }
    free(li);
  }
  free((*trie)->transition);
  free((*trie)->finite);
  free((*trie));
  *trie = NULL;
}

#endif

Trie prefixTrie(unsigned char *word) {
	int len = wordLength(word, END_INDICATOR);
  Trie t = createTrie((int)len + 1);
	unsigned char p[len + 1];
  memcpy(p, word, (size_t) len + 1);
  for (int k = len; k > 0; --k) {
    p[k] = END_INDICATOR;
		insertInTrie(t, p);
  }
	return t;
}


Trie suffixTrie(unsigned char *word) {
  int len = (int) strlen((char *) word);
  int size = len * (len + 1) / 2;
  Trie t = createTrie(size + 1);
  unsigned char *p = word;
  while (*p != END_INDICATOR) {
		insertInTrie(t, p);
    ++p;
  }
  return t;
}

Trie factorTrie(unsigned char *word) {
  Trie t = suffixTrie(word);
  for (int i = 0; i < t->maxNode; ++i) {
    t->finite[i] = 1;
  }
  return t;
}


int wordLength(unsigned char *w, unsigned char e) {
  unsigned char *p = w;
  while (*p != e) {
    ++p;
  }
  return (int)(p - w);
}

