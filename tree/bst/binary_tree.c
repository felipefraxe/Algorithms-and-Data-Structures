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
    root = insert_node(root, create_node(num[i]));
  root = remove_node(root, 100);
  tree *found = search(root, 86);
  found ? printf("Found %d\n", found->key) : printf("Couldn't find the key\n");
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

tree* insert_node(tree *root, tree *node)
{
  if(!root)
    return node;
  if(root->key == node->key)
  {
    printf("Repeated key\n");
    free(node);
    return root;
  }
  node->key > root->key ? (root->right = insert_node(root->right, node)) : (root->left = insert_node(root->left, node));
  return root;
}

tree* search(tree *root, int key)
{
  if(!root || root->key == key)
    return root;
  return root->key < key ? search(root->right, key) : search(root->left, key);
}

tree* find_min(tree *root)
{
  if(!root->left)
    return root;
  return find_min(root->left);   
}

tree* remove_node(tree *root, int key)
{
  if(!root)
    return root;  
  tree *right = root->right, *left = root->left;
  if(root->key == key)
  {
    if(right == left)
    {
      free(root);
      return NULL;
    }
    if(!right)
    {
      free(root);
      return left;
    }
    if(!left)
    {
      free(root);
      return right;
    }
    root->key = find_min(right)->key;
    root->right = remove_node(right, root->key);
    return root;
  }
  root->key < key ? (root->right = remove_node(root->right, key)) : (root->left = remove_node(root->left, key));
  return root;
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