#ifndef AVL_H
#define AVL_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node
{
    int key;
    int height;
    struct node *left;
    struct node *right;
} avl_node_t;

typedef struct
{
    avl_node_t *root;
} avl_tree_t;

bool avl_empty(avl_tree_t *tree);
void avl_free(avl_tree_t *tree);
void avl_init(avl_tree_t *tree);
void avl_insert(avl_tree_t *tree, int key);
void avl_print_tree(avl_tree_t *tree);
void avl_remove(avl_tree_t *tree, int key);
int avl_get(avl_tree_t *tree, int key);

#endif