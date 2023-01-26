#ifndef BTREE_H
#define BTREE_H

#include "structs.h"
#include "list/list.h"

// Prototypes for Btree functions
Btree* search(Btree *root, int key);
Btree* create_node(void);
int binsearch(int array[], int low, int high, int num);
void copy_array(Btree *source, Btree *root, int start, int end);
void insert_sorted(Btree *node, int index, int num);
void insert_key(Btree **root, int key, list **parent);
void split_node(Btree **root, list **parent, int key, int mid);
void remove_sorted(Btree *node, int index);
int find_max_in_min_child(Btree *node);
int find_min_in_max_child(Btree *node);
void left_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index);
void right_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index);
int find_child(Btree *root, Btree *child);
void adjust_root(Btree *root, list **parent);
void move_array(Btree *source, Btree *dest, int end);
void merge_node(Btree **parent_root, Btree *sibling, Btree *root, int parent_index, list **parent);
void remove_key(Btree **root, int key, list **parent);
void printf_tree(Btree *root);
void deallocate(Btree *root);

#endif