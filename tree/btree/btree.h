#ifndef BTREE_H
#define BTREE_H

#include "structs.h"
#include "list/list.h"

// Prototypes for Btree functions
Btree* search(Btree *root, MyData data);
int is_leaf(Btree *this);
Btree* create_node(void);
int binsearch(void *array, size_t size, int low, int high, void *key, int (* cmp)(const void *, const void *));
int cmpMyData(const void *data1, const void *data2);
void copy_array(Btree *source, Btree *root, int start, int end);
void insert_sorted(Btree *node, int index, MyData new_data);
void insert_key(Btree **root, MyData new_data, list **parent);
void split_node(Btree **root, list **parent, MyData new_data, int mid);
void remove_sorted(Btree *node, int index);
MyData find_max_in_min_child(Btree *node);
MyData find_min_in_max_child(Btree *node);
void left_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index);
void right_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index);
int find_child(Btree *root, Btree *child);
void adjust_root(Btree *root, list **parent);
void move_array(Btree *source, Btree *dest, int end);
void merge_node(Btree **parent_root, Btree *sibling, Btree *root, int parent_index, list **parent);
void remove_key(Btree **root, MyData rmv_data, list **parent);
void printf_tree(Btree *node);
void deallocate(Btree *node);

#endif