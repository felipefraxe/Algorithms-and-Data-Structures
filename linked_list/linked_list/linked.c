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
  head = reverse(head);
  printf_list(head);
  printf("length: %d\n", length(head));
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
  node->next = head;
  return node;
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

int length(list *head)
{
  int len = 0;
  while(head)
  {
    len++;
    head = head->next;
  }
  return len;
}

list* reverse(list *head)
{
  list *previous = NULL, *next = head->next;
  while(next)
  {
    head->next = previous;
    previous = head;
    head = next;
    next = head->next;
  }
  head->next = previous;
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