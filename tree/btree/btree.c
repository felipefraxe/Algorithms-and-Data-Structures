/*
  Code written by Felipe Fraxe
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
  /* for(int i = 0; i < size; i++)
    remove_key(&root, num[i], &stack); */
  printf_tree(root, 0);
  deallocate(root);
  return EXIT_SUCCESS;
}

Btree* create_node()
{
  Btree *node = malloc(sizeof(Btree));
  if(!node)
  {
    printf("Could not allocate memory for node. Something went wrong\n");
    exit(EXIT_FAILURE);
  }
  node->keys_count = 0;
  for(int i = 0; i < ORDER + 1; i++)
    node->children[i] = NULL;
  return node;
}

int binary_search_index(int *array, int left, int right, int num)
{
  int mid = left + (right - left) / 2;
  while(left <= right)
  {
    if(num > array[mid])
      left = mid + 1;
    else if(num < array[mid])
      right = mid - 1;
    else
      return mid;
    mid = left + (right - left) / 2;
  }
  return mid;
}

void insert_sorted(Btree *root, int size, int index, int num)
{
  int i = size-1; 
  while(i >= index)
  {
    root->keys[i+1] = root->keys[i];
    root->children[i+2] = root->children[i+1];
    i--;
  }
  if(i < (size - 1))
    root->children[i+2] = root->children[i+1];
  root->keys[index] = num;
}

void copy_array(Btree *source, Btree *root, int start, int end)
{
  for(int i = start; i < end; i++)
  {
    root->keys[i-start] = source->keys[i];
    root->children[i-start] = source->children[i];
  }
  root->children[end-start] = source->children[end];
}

void split_node(Btree **root, list **parent, int key, int mid)
{
  int index;
  Btree *new_root, *left, *right;

  left = create_node();
  copy_array(*root, left, 0, mid);
  left->keys_count = mid;

  right = create_node();
  copy_array(*root, right, mid+1, ORDER);
  right->keys_count = ORDER % 2 == 0 ? mid + 1 : mid;

  if(*parent)
  {
    free(*root);
    root = (*parent)->root;
    pull(parent);
  }
  else
    (*root)->keys_count = 0;

  index = binary_search_index((*root)->keys, 0, (*root)->keys_count - 1, key);
  insert_sorted(*root, (*root)->keys_count, index, key);
  (*root)->children[index] = left;
  (*root)->children[index+1] = right;

  if((*root)->keys_count < ORDER-1)
    (*root)->keys_count++;
  else
  {
    mid = (*root)->keys_count / 2;
    key = (*root)->keys[mid];
    split_node(root, parent, key, mid);
  }
}

void insert_key(Btree **root, int key, list **parent)
{
  int index, mid;

  if(!*root && !*parent)
  {
    *root = create_node();
    (*root)->keys[0] = key;
    (*root)->keys_count++;
    return;
  }

  index = binary_search_index((*root)->keys, 0, (*root)->keys_count - 1, key);
  if(index < (*root)->keys_count && (*root)->keys[index] == key)
  {
    printf("Reapeated key %d!\n", key);
    return;
  }

  if(!(*root)->children[index])
  {
    insert_sorted(*root, (*root)->keys_count, index, key);
    if((*root)->keys_count < ORDER-1)
      (*root)->keys_count++;
    else
    {
      mid = (*root)->keys_count / 2;
      key = (*root)->keys[mid];
      split_node(root, parent, key, mid);
    }
    return;
  }
  push(parent, new_node(root));
  insert_key(&(*root)->children[index], key, parent);
  pull(parent);
}

void remove_sorted(Btree *root, int size, int index)
{
  for(int i = index; i < size; i++)
  {
    root->keys[i] = root->keys[i+1];
    root->children[i] = root->children[i+1];
  }
  root->children[size] = NULL;
  root->keys_count--;
}

int find_max_min(Btree *root)
{
  while(root->children[root->keys_count])
    root = root->children[root->keys_count];
  if(root->keys_count > MIN)
    return root->keys[root->keys_count - 1];
  return -1;
}

int find_min_max(Btree *root)
{
  while(root->children[0])
    root = root->children[0];
  return root->keys[0];
}

void left_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
  root->keys[root->keys_count++] = parent->keys[parent_index];
  root->children[root->keys_count] = sibling->children[0];
  parent->keys[parent_index] = sibling->keys[0];
  remove_sorted(sibling, sibling->keys_count, 0);
}

void right_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
  Btree *overwritten;

  root->keys_count++;
  insert_sorted(root, root->keys_count, 0, parent->keys[parent_index]);
  parent->keys[parent_index] = sibling->keys[sibling->keys_count-1];
  root->children[0] = sibling->children[sibling->keys_count];
  overwritten = sibling->children[sibling->keys_count-1];
  remove_sorted(sibling, sibling->keys_count, sibling->keys_count-1);
  sibling->children[sibling->keys_count] = overwritten;
}

int find_child(Btree *root, Btree *child)
{
  for(int i = 0; i < root->keys_count + 1; i++)
  {
    if(root->children[i] == child)
      return i;
  }
  return -1;
}

void adjust_root(Btree *root, list **parent)
{
  Btree **parent_root = (*parent)->root, *sibling;
  int parent_index = find_child(*parent_root, root);
  pull(parent);

  if(parent_index > 0)
  {
    sibling = (*parent_root)->children[parent_index-1];
    if(sibling->keys_count > MIN)
    {
      right_rotation(root, sibling, *parent_root, parent_index-1);
      return;
    }
    else if(parent_index == (*parent_root)->keys_count)
    {
      merge_node(parent_root, sibling, root, parent_index, parent);
      return;
    }
  }
  sibling = (*parent_root)->children[parent_index+1];
  if(sibling->keys_count > MIN)
    left_rotation(root, sibling, *parent_root, parent_index);
  else
    merge_node(parent_root, sibling, root, parent_index, parent);
}

void move_array(Btree *source, Btree *root, int end)
{
  for(int i = 0; i < end; i++)
  {
    root->keys[root->keys_count] = source->keys[i];
    root->children[root->keys_count] = source->children[i];
    root->keys_count++;
  }
  root->children[root->keys_count] = source->children[end];
}

void merge_node(Btree **parent_root, Btree *sibling, Btree *root, int parent_index, list **parent)
{
  if(parent_index > 0 && (*parent_root)->children[parent_index-1] == sibling)
  {
    sibling->keys[sibling->keys_count++] = (*parent_root)->keys[parent_index-1];
    move_array(root, sibling, root->keys_count);
    remove_sorted(*parent_root, (*parent_root)->keys_count, parent_index-1);
    (*parent_root)->children[parent_index-1] = sibling;
    free(root);
    root = NULL;
  }
  else
  {
    root->keys[root->keys_count++] = (*parent_root)->keys[parent_index];
    move_array(sibling, root, sibling->keys_count);
    remove_sorted(*parent_root, (*parent_root)->keys_count, parent_index);
    (*parent_root)->children[parent_index] = root;
    free(sibling);
    sibling = NULL;
  }

  if(!*parent && (*parent_root)->keys_count == 0)
  {
    free(*parent_root);
    *parent_root = sibling ? sibling : root;
  }
  else if(*parent && (*parent_root)->keys_count < MIN)
    adjust_root(*parent_root, parent);
}

void remove_key(Btree **root, int key, list **parent)
{
  int index, parent_index, max_min;
  Btree *sibling, **parent_address;

  if(*root)
  {
    index = binary_search_index((*root)->keys, 0, (*root)->keys_count - 1, key);
    if(index < (*root)->keys_count && (*root)->keys[index] == key)
    {
      if(!(*root)->children[index])
      {
        remove_sorted(*root, (*root)->keys_count, index);
        if((*root)->keys_count >= MIN || !*parent)
        {
          if((*root)->keys_count == 0)
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
          if(sibling->keys_count > MIN)
          {
            right_rotation(*root, sibling, *parent_address, parent_index-1);
            return;
          }
          if(parent_index == (*parent_address)->keys_count)
          {
            merge_node(parent_address, sibling, *root, parent_index, parent);
            return;
          }
        }
        sibling = (*parent_address)->children[parent_index+1];
        if(sibling->keys_count > MIN)
          left_rotation(*root, sibling, *parent_address, parent_index);
        else
          merge_node(parent_address, sibling, *root, parent_index, parent);
        return;
      }
      else
      {
        max_min = find_max_min((*root)->children[index]);
        if(max_min > 0)
          (*root)->keys[index] = key = max_min;
        else
        {
          (*root)->keys[index] = key = find_min_max((*root)->children[index + 1]);
          index++;
        }
      }
    }
    push(parent, new_node(root));
    remove_key(&(*root)->children[index], key, parent);
    pull(parent);
  }
}

Btree* search(Btree *root, int key)
{
  if(root)
  {
    int index;
    while(root)
    {
      index = binary_search_index(root->keys, 0, root->keys_count - 1, key);
      if(root->keys[index] == key)
        return root;
      root = root->children[index];
    }
  }
  return root;
}

void printf_tree(Btree *root, int index)
{
  int keys_size, children_size;
  if(root)
  {
    keys_size = root->keys_count;
    children_size = keys_size + 1;
    if(index < children_size)
    {
      printf_tree(root->children[index], 0);
      if(index < keys_size)
        printf("%d\n", root->keys[index]);
      printf_tree(root, index + 1);
    }
  }
}

void deallocate(Btree *root)
{
  if(root)
  {
    int children_size = root->keys_count + 1;
    for(int i = 0; root->children[i] && i < children_size; i++)
        deallocate(root->children[i]);
    free(root);
  }
}