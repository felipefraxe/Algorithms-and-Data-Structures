/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "linked.h"

int main(void)
{
  head = insert_node(head, create_node(30));
  head = insert_node(head, create_node(25));
  head = insert_node(head, create_node(45));
  head = insert_node(head, create_node(50));
  head = insert_node(head, create_node(75));
  head = insert_node(head, create_node(100));
  head = remove_node(head, 100);
  list *found = search(head, 50);
  found && printf("%d\n", found->key);
  printf_list(head);
  deallocate_list(head);
  return EXIT_SUCCESS;
}

list* create_node(int key)
{
  list *node = malloc(sizeof(list));
  if(!node)
  {
    printf("Could not allocate memory for node. Something went wrong\n");
    exit(EXIT_FAILURE);
  }
  node->key = key;
  node->next = NULL;
  return node;
}

list* insert_node(list *head, list *node)
{
  if(!head)
    return node;
  head->next = insert_node(head->next, node);
  return head;
}

list* search(list *head, int key)
{
  while(head)
  {
    if(head->key == key)
      return head;
    head = head->next;
  }
  return NULL;
}

list* remove_node(list *head, int key)
{
  if(!head)
    return head;
  if(head->key == key)
  {
    list *tmp = head;
    head = head->next;
    free(tmp);
    return head;
  }
  head->next = remove_node(head->next, key);
  return head;
}

void printf_list(list *head)
{
  for(head; head; head = head->next)
    printf("%d ", head->key);
  printf("\n");
}

void deallocate_list(list *head)
{
  while(head)
  {
    list *tmp = head->next;
    free(head);
    head = tmp;
  }
}