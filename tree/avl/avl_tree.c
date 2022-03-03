/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "avl_tree.h"
int max(int num1, int num2);

int main(void)
{
  int num[] = { 42, 51, 16, 19, 56, 37, 42, 86, 71, 10, 75, 22, 87, 31, 42, 65, 11, 94, 43, 18 };
  int size = sizeof(num) / sizeof(num[0]);
  for(int i = 0; i < size; i++)
    root = insert_node(root, create_node(num[i]));
  root = remove_node(root, 100);
  printf_tree(root);
  deallocate(root);
  return EXIT_SUCCESS;
}

avl_tree* create_node(int key)
{
  avl_tree *node = malloc(sizeof(avl_tree));
  if(!node)
  {
    printf("Could not allocate memory for node. Something went wrong\n");
    exit(EXIT_FAILURE);
  }
  node->key = key;
  node->left = node->right = NULL;
  return node;
}

avl_tree* insert_node(avl_tree *root, avl_tree *node)
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
  return balance(root);
}

avl_tree* search(avl_tree *root, int key)
{
  while(root)
  {
    if(root->key == key)
      return root;
    root = key > root->key ? root->right : root->left;
  }
  return NULL;
}

avl_tree* find_min(avl_tree *root)
{
  while(root->left)
    root = root->left;
  return root;
}

avl_tree* remove_node(avl_tree *root, int key)
{
  if(!root)
    return root;
  avl_tree *right = root->right, *left = root->left;
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
    return balance(root);
  }
  root->key < key ? (root->right = remove_node(root->right, key)) : (root->left = remove_node(root->left, key));
  return balance(root);
}

void deallocate(avl_tree *root)
{
  if(root)
  {
    deallocate(root->left);
    deallocate(root->right);
    free(root);
  }
}

void printf_tree(avl_tree *root)
{
  if(root)
  {
    printf_tree(root->left);
    printf("%d, BALANCE: %d\n", root->key, balance_factor(root));
    printf_tree(root->right);
  }
}

int max(int num1, int num2)
{
  return num1 > num2 ? num1 : num2;
}

int node_height(avl_tree *root)
{
  if(root)
    return 1 + max(node_height(root->left), node_height(root->right));
  return -1;
}

int balance_factor(avl_tree *root)
{
  if(root)
    return (node_height(root->left) - node_height(root->right));
  return 0;
}

avl_tree* balance(avl_tree *root)
{
  int value = balance_factor(root);
  if(value > 1)
  {
    if(balance_factor(root->left) > 0)
      return right_rotation(root);
    root->left = left_rotation(root->left);
    return right_rotation(root);
  }
  if(value < -1)
  {
    if(balance_factor(root->right) < 0)
      return left_rotation(root);
    root->right = right_rotation(root->right);
    return left_rotation(root);
  }
  return root;
}

avl_tree* right_rotation(avl_tree *root)
{
  avl_tree *new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

avl_tree* left_rotation(avl_tree *root)
{
  avl_tree *new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;
  return new_root;
}