#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree
{
  int key;
  struct avl_tree *left, *right;
}
avl_tree;

// Helpers functions
int node_height(avl_tree *root);
int balance_factor(avl_tree *root);
avl_tree* find_min(avl_tree *root);
avl_tree* create_node(int key);
avl_tree* search(avl_tree *root, int num);
avl_tree* right_rotation(avl_tree *root);
avl_tree* left_rotation(avl_tree *root);

// Main operations
void remove_node(avl_tree **root, int num);
void insert_node(avl_tree **root, avl_tree *n);
void balance(avl_tree **root);
void printf_tree(avl_tree *root);
void deallocate(avl_tree *root);

// Initialize tree
avl_tree *root = NULL;

#endif