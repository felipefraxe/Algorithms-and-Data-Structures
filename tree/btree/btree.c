/*
  Code written by Felipe Fraxe
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "btree.h"

Btree *root = NULL;
list *stack = NULL;

int main(void)
{
  int num[] = { 30, 20, 40, 50, 2, 10, 18, 7, 15, 16, 25, 60, 1, 70, 55, 66, 14, 51, 92, 115, 17, 134, 23, 565,
    19, 42, 37, 58, 32, 47, 214, 354, 666, 789, 74, 539, 452, 810, 1024, 1120, 701, 234, 568, 982, 703, 459, 327,
    882, 694, 702, 557, 210, 212, 387, 10534, 862, 303, 549, 100, 22, 21, 27, 9, 6 };
  int size = sizeof(num) / sizeof(num[0]);
  for(int i = 0; i < size; i++)
      insert_key(&root, num[i], &stack);
  for(int i = 0; i < size; i++)
      remove_key(&root, num[i], &stack);
  printf_tree(root);
  deallocate(root);
  return EXIT_SUCCESS;
}

Btree* create_node()
{
    Btree *node = calloc(1, sizeof(Btree));
    if(node == NULL)
    {
        perror("Failed to allocate memory for new node. Exiting...\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

int binsearch(int array[], int low, int high, int num)
{
    int mid = low + (high - low) / 2;
    while(low <= high)
    {
        if(num > array[mid])
            low = mid + 1;
        else if(num < array[mid])
            high = mid - 1;
        else
            return mid;
        mid = low + (high - low) / 2;
    }
    return mid;
}

void insert_sorted(Btree *node, int index, int num)
{
    for(int i = node->num_keys; i > index; i--)
    {
        node->keys[i] = node->keys[i-1];
        node->children[i+1] = node->children[i];
    }
    node->keys[index] = num;
}

void copy_array(Btree *source, Btree *dest, int start, int end)
{
    for(int i = start; i < end; i++)
    {
        dest->keys[i-start] = source->keys[i];
        dest->children[i-start] = source->children[i];
    }
    dest->children[end-start] = source->children[end];
}


void split_node(Btree **root, list **parent, int key, int mid)
{
    int index;
    Btree *left, *right;

    left = create_node();
    copy_array(*root, left, 0, mid);
    left->num_keys = mid;

    right = create_node();
    copy_array(*root, right, mid+1, ORDER);
    right->num_keys = ORDER % 2 == 0 ? mid + 1 : mid;

    if(*parent)
    {
        free(*root);
        root = (*parent)->root;
        pull(parent);
    }
    else
        (*root)->num_keys = 0;

    index = binsearch((*root)->keys, 0, (*root)->num_keys - 1, key);
    insert_sorted(*root, index, key);
    (*root)->children[index] = left;
    (*root)->children[index+1] = right;

    if((*root)->num_keys < ORDER-1)
        (*root)->num_keys++;
    else
    {
        mid = (*root)->num_keys / 2;
        key = (*root)->keys[mid];
        split_node(root, parent, key, mid);
    }
}

void insert_key(Btree **root, int key, list **parent)
{
    int index, mid;

    if(*root == NULL && *parent == NULL)
    {
        *root = create_node();
        (*root)->keys[0] = key;
        (*root)->num_keys++;
        return;
    }

    index = binsearch((*root)->keys, 0, (*root)->num_keys - 1, key);
    if(index < (*root)->num_keys && (*root)->keys[index] == key)
    {
        printf("Reapeated key %d!\n", key);
        return;
    }

    if((*root)->children[index] == NULL)
    {
        insert_sorted(*root, index, key);
        if((*root)->num_keys < ORDER-1)
            (*root)->num_keys++;
        else
        {
            mid = (*root)->num_keys / 2;
            key = (*root)->keys[mid];
            split_node(root, parent, key, mid);
        }
        return;
    }
    push(parent, new_node(root));
    insert_key(&(*root)->children[index], key, parent);
    pull(parent);
}

void remove_sorted(Btree *node, int index)
{
    for(int i = index; i < node->num_keys; i++)
    {
        node->keys[i] = node->keys[i+1];
        node->children[i] = node->children[i+1];
    }
    node->children[node->num_keys] = NULL;
    node->num_keys--;
}

int find_max_in_min_child(Btree *node)
{
    while(node->children[node->num_keys])
        node = node->children[node->num_keys];
    return node->keys[node->num_keys - 1];
}

int find_min_in_max_child(Btree *node)
{
    while(node->children[0])
        node = node->children[0];
    return node->keys[0];
}

void left_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
    root->keys[root->num_keys++] = parent->keys[parent_index];
    root->children[root->num_keys] = sibling->children[0];
    parent->keys[parent_index] = sibling->keys[0];
    remove_sorted(sibling, 0);
}

void right_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
    root->num_keys++;
    insert_sorted(root, 0, parent->keys[parent_index]);
    parent->keys[parent_index] = sibling->keys[sibling->num_keys-1];
    root->children[0] = sibling->children[sibling->num_keys];
    sibling->children[sibling->num_keys] = NULL;
    sibling->num_keys--;
}

int find_child(Btree *root, Btree *child)
{
    int low = 0, high = root->num_keys + 1;
    int mid = high / 2;
    while(low <= high)
    {
        if(root->children[mid] == child)
            return mid;
        if(root->children[mid]->keys[0] < child->keys[0])
            low = mid + 1;
        else
            high = mid - 1;
        mid = (high + low) / 2;
    }
    return -1;
}

void adjust_root(Btree *root, list **parent)
{
    Btree **parent_root = (*parent)->root, *sibling;
    int parent_index = find_child(*parent_root, root);
    pull(parent);

    if(parent_index == 0)
    {
        sibling = (*parent_root)->children[parent_index+1];
        if(sibling->num_keys > MIN)
            left_rotation(root, sibling, *parent_root, parent_index);
        else
            merge_node(parent_root, sibling, root, parent_index, parent);
        return;
    }
    sibling = (*parent_root)->children[parent_index-1];
    if(sibling->num_keys > MIN)
        right_rotation(root, sibling, *parent_root, parent_index-1);
    else if(parent_index == (*parent_root)->num_keys)
        merge_node(parent_root, sibling, root, parent_index, parent);
}

void move_array(Btree *source, Btree *dest, int end)
{
    for(int i = 0; i < end; i++)
    {
        dest->keys[dest->num_keys] = source->keys[i];
        dest->children[dest->num_keys] = source->children[i];
        dest->num_keys++;
    }
    dest->children[dest->num_keys] = source->children[end];
    free(source);
    source = NULL;
}

void merge_node(Btree **parent_root, Btree *sibling, Btree *root, int parent_index, list **parent)
{
    if(parent_index > 0 && (*parent_root)->children[parent_index-1] == sibling)
    {
        sibling->keys[sibling->num_keys++] = (*parent_root)->keys[parent_index-1];
        move_array(root, sibling, root->num_keys);
        remove_sorted(*parent_root, parent_index-1);
        (*parent_root)->children[parent_index-1] = sibling;
    }
    else
    {
        root->keys[root->num_keys++] = (*parent_root)->keys[parent_index];
        move_array(sibling, root, sibling->num_keys);
        remove_sorted(*parent_root, parent_index);
        (*parent_root)->children[parent_index] = root;
    }

    if(*parent == NULL && (*parent_root)->num_keys == 0)
    {
        free(*parent_root);
        *parent_root = sibling != NULL ? sibling : root;
    }
    else if(*parent != NULL && (*parent_root)->num_keys < MIN)
        adjust_root(*parent_root, parent);
}

void remove_key(Btree **root, int key, list **parent)
{
    int index, parent_index, max_min;
    Btree *sibling, **parent_address;

    if(*root == NULL)
      return;

    index = binsearch((*root)->keys, 0, (*root)->num_keys - 1, key);
    if(index < (*root)->num_keys && (*root)->keys[index] == key)
    {
        if((*root)->children[index] == NULL)
        {
            remove_sorted(*root, index);
            if((*root)->num_keys >= MIN || *parent == NULL)
            {
                if((*root)->num_keys == 0)
                {
                    free(*root);
                    *root = NULL; 
                }
                return;
            }
            parent_address = (*parent)->root;
            pull(parent);
            parent_index = find_child(*parent_address, *root);
            if(parent_index > 0)
            {
                sibling = (*parent_address)->children[parent_index-1];
                if(sibling->num_keys > MIN)
                {
                    right_rotation(*root, sibling, *parent_address, parent_index-1);
                    return;
                }
                if(parent_index == (*parent_address)->num_keys)
                {
                    merge_node(parent_address, sibling, *root, parent_index, parent);
                    return;
                }
            }
            sibling = (*parent_address)->children[parent_index+1];
            if(sibling->num_keys > MIN)
                left_rotation(*root, sibling, *parent_address, parent_index);
            else
                merge_node(parent_address, sibling, *root, parent_index, parent);
            return;
        }
        else
        {
            if((*root)->children[index]->num_keys > MIN)
            {
                key = find_max_in_min_child((*root)->children[index]);
                (*root)->keys[index] = key;
            }
            else
            {
                key = find_min_in_max_child((*root)->children[index + 1]);
                (*root)->keys[index] = key;
                index++;
            }
        }
    }
    push(parent, new_node(root));
    remove_key(&(*root)->children[index], key, parent);
    pull(parent);
}

Btree* search(Btree *root, int key)
{
    int index;
    while(root != NULL)
    {
        index = binsearch(root->keys, 0, root->num_keys - 1, key);
        if(root->keys[index] == key)
            return root;
        root = root->children[index];
    }
    return root;
}

void printf_tree(Btree *root)
{
    if(root == NULL)
        return;

    int i = 0;
    printf_tree(root->children[i]);
    while(i < root->num_keys)
    {
        printf("%d\n", root->keys[i]);
        printf_tree(root->children[++i]);
    }
}

void deallocate(Btree *root)
{
    if(root == NULL)
        return;

    int children_size = root->num_keys + 1;
    for(int i = 0; root->children[i] != NULL && i < children_size; i++)
        deallocate(root->children[i]);
    free(root);
}