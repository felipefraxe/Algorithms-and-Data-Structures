#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct tree
{
  int key;
  struct tree *left, *right;
}
tree;

//Prototypes for binary search tree
tree* search(tree *root, int num);
tree* find_min(tree *root);
tree* remove_node(tree *root, int num);
tree* create_node(int key);
tree* insert_node(tree *root, tree *n);
void printf_tree(tree *root);
void deallocate(tree *root);

tree *root = NULL;

#endif