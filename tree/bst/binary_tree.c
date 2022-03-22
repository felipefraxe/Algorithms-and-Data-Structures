/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "binary_tree.h"

int main(void)
{
  int num[] = { 42, 51, 16, 19, 56, 37, 42, 86, 71, 10, 75, 22, 87, 31, 42, 65, 11, 94, 43, 18 };
  int size = sizeof(num) / sizeof(num[0]);
  for(int i = 0; i < size; i++)
    insert_node(&root, create_node(num[i]));
  remove_node(&root, 42);
  tree *found = search(root, 86);
  found && printf("Found %d\n", found->key);
  printf_tree(root);
  deallocate(root);
  return EXIT_SUCCESS;
}

tree* create_node(int key)
{
  tree *node = malloc(sizeof(tree));
  if(!node)
  {
    printf("Could not allocate memory for node. Something went wrong\n");
    exit(EXIT_FAILURE);
  }
  node->key = key;
  node->left = node->right = NULL;
  return node;
}

void insert_node(tree **root, tree *node)
{
  tree *tmp = *root, *parent = NULL;
  while(tmp)
  {
    if(tmp->key == node->key)
    {
      printf("Repeated key\n");
      free(node);
      return;
    }
    parent = tmp;
    tmp = node->key > tmp->key ? tmp->right : tmp->left;
  }
  if(parent)
    parent->key > node->key ? (parent->left = node) : (parent->right = node);
  else
    *root = node;
}

tree* search(tree *root, int key)
{
  while(root)
  {
    if(root->key == key)
      return root;
    root = key > root->key ? root->right : root->left;
  }
  return NULL;
}

tree* find_min(tree *root)
{
  while(root->left)
    root = root->left;
  return root;
}

void remove_node(tree **root, int key)
{
  tree *tmp = *root, *parent = NULL;
  while(tmp)
  {
    if(tmp->key == key)
    {
      if(tmp->right && tmp->left)
      {
        key = tmp->key = find_min(tmp->right)->key;
        parent = tmp;
        tmp = tmp->right;
        continue;
      }
      if(!parent)
        *root = tmp->left ? tmp->left : tmp->right;
      else if(tmp->right == tmp->left)
        key >= parent->key ? (parent->right = NULL) : (parent->left = NULL);
      else if(!tmp->right)
        key >= parent->key ? (parent->right = tmp->left) : (parent->left = tmp->left);
      else
        key >= parent->key ? (parent->right = tmp->right) : (parent->left = tmp->right);
      free(tmp);
      return;
    }
    parent = tmp;
    tmp = key > tmp->key ? tmp->right : tmp->left;
  }
}

void deallocate(tree *root)
{
  if(root)
  {
    deallocate(root->left);
    deallocate(root->right);
    free(root);
  }
}

void printf_tree(tree *root)
{
  if(root)
  {
    printf_tree(root->left);
    printf("%d\n", root->key);
    printf_tree(root->right);
  }
}