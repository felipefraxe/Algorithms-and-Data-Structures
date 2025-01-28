#ifndef TRIE_H
#define TRIE_H

#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct Trie_Node
{
    bool EOW;
    struct Trie_Node children[ALPHABET_SIZE];
} Trie_Node;

typedef struct Trie
{
    Trie_Node *root;
} Trie;

Trie trie_constructor(void);
bool trie_insert(const char *str, Trie *trie);
bool trie_search(const char *str, Trie *trie);
bool trie_unload(Trie *trie);

Trie_Node *trie_create_node(void);
void trie_unloader(Trie_Node *curr);

#endif