#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

list* new_node(Btree **root)
{
  list *node = malloc(sizeof(list));
  if(!node)
  {
    printf("Could not allocate memory for node. Something went wrong\n");
    exit(EXIT_FAILURE);
  }
  node->root = root;
  node->next = NULL;
  return node;
}

void push(list **stack, list *node)
{
  if(*stack)
    node->next = *stack;
  *stack = node;
}

void pull(list **stack)
{
  if(*stack)
  {
    list *tmp = (*stack)->next;
    free(*stack);
    *stack = tmp;
  }
}

void deallocate_stack(list *stack)
{
  while(stack)
  {
    list *tmp = stack->next;
    free(stack);
    stack = tmp;
  }
}