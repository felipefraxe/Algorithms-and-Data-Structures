#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree
{
  int key;
  struct avl_tree *left, *right;
}
avl_tree;

int node_height(avl_tree *root);
int balance_factor(avl_tree *root);
avl_tree* search(avl_tree *root, int num);
avl_tree* find_min(avl_tree *root);
avl_tree* remove_node(avl_tree *root, int num);
avl_tree* create_node(int key);
avl_tree* insert_node(avl_tree *root, avl_tree *n);
avl_tree* balance(avl_tree *root);
avl_tree* right_rotation(avl_tree *root);
avl_tree* left_rotation(avl_tree *root);
void printf_tree(avl_tree *root);
void deallocate(avl_tree *root);

avl_tree *root = NULL;

#endif