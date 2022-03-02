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
  for(head; head; head = head->next)
  {
    if(head->key == key)
      return head;
  }
  return NULL;
}

list* remove_node(list *head, int key)
{
  if(!head)
    return head;
  list *tmp = head, *previous = head;
  if(head->key == key)
  {
    head = head->next;
    free(tmp);
    return head;
  }
  for(previous = head, tmp = tmp->next; tmp; previous = tmp, tmp = tmp->next)
  {
    if(tmp->key == key)
    {
      previous->next = tmp->next;
      free(tmp);
      return head;
    }
  }
  return head;
}

int length(list *head)
{
  int len = 0;
  for(head; head; head = head->next)
    len++;
  return len;
}

list* reverse(list *head)
{
  if(!head)
    return head;
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