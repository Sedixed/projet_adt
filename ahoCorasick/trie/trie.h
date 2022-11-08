#ifndef H__TRIE
#define H__TRIE

// 1 Si l'on utilise la représentation avec des tables de hachage, 0 sinon
#define USE_HASH 1

typedef struct _trie *Trie;

#define END_INDICATOR '\0'



// Renvoie une structure représentant un trie, de taille maximale initiale maxNode. Renvoie NULL en cas d'erreur
extern Trie createTrie(int maxNode);

// Insère le mot pointé par w dans trie. La fin du mot est indiquée par la valeur END_INDICATOR.
extern void insertInTrie(Trie trie, unsigned char *w);

// Indique la présence du mot pointé par w dans trie. La fin du mot w est indiquée par la valeur END_INDICATOR. Retourne 0 si le mot w n'est pas présent, 1 sinon.
extern int isInTrie(Trie trie, unsigned char *w);

// Désalloue les ressources associées à *trie.
extern void disposeTrie(Trie *trie);

// Crée un trie constitué des préfixes du mot word. renvoie NULL en cas d'erreur
extern Trie prefixTrie(unsigned char *word);

// Crée un trie constitué des suffixes du mot word. renvoie NULL en cas d'erreur
extern Trie suffixTrie(unsigned char *word);

// Crée un trie constitué des facteurs du mot word. renvoie NULL en cas d'erreur
extern Trie factorTrie(unsigned char *word);

#endif
