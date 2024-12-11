#include <trie.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Trie trie_constructor(void)
{
    Trie trie = { trie_create_node() };
    return trie;
}

Trie_Node *trie_create_node(void)
{
    Trie_Node *root = malloc(sizeof(Trie_Node));
    memset(root->children, 0, ALPHABET_SIZE);
    root->EOW = false;
    return root;
}

bool trie_insert(const char *str, Trie *trie)
{
    Trie_Node *curr = trie->root;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        int key = tolower(str[i]) - 'a';
        if (curr->children[key] == NULL)
        {
            curr->children[key] = malloc(sizeof(Trie_Node));
            if (curr->children[key] == NULL)
                return false;
        }
        curr = curr->children[key];
    }
    curr->EOW = true;
    return true;
}

bool trie_search(const char *str, Trie *trie)
{
    Trie_Node *curr = trie->root;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        int key = tolower(str[i]) - 'a';
        if (curr->children[key] == NULL)
            return false;
        curr = curr->children[key];
    }
    return curr->EOW;
}

bool trie_unload(Trie *trie)
{
    trie_unloader(trie->root);
    return true;
}

void trie_unloader(Trie_Node *curr)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (curr->children[i] != NULL)
            trie_unloader(curr->children[i]);
    }
    free(curr);
}