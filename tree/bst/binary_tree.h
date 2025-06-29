#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
} node_t;

typedef struct
{
  int key;
  struct tree *left, *right;
} bintree_t;

//Prototypes for binary search tree
tree* search(tree *root, int num);
tree* find_min(tree *root);
void remove_node(tree **root, int num);
tree* create_node(int key);
void insert_node(tree **root, tree *n);
void printf_tree(tree *root);
void deallocate(tree *root);

tree *root = NULL;

#endif