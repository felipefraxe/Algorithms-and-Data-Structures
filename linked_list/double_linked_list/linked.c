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
  insert_node_front(&head, &tail, create_node(30));
  insert_node_front(&head, &tail, create_node(25));
  insert_node_back(&head, &tail, create_node(45));
  insert_node_front(&head, &tail, create_node(50));
  insert_node_front(&head, &tail, create_node(75));
  insert_node_back(&head, &tail, create_node(100));
  list *found = search(head, tail, 100);
  found && printf("found\n");
  remove_node(&head, &tail, 100);
  printf_list(head);
  printf_list_reverse(tail);
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
  node->previous = NULL;
  return node;
}

void insert_node_front(list **head, list **tail, list *node)
{
  if(!*tail)
    *tail = *head = node;
  else
  {
    node->previous = *tail;
    (*tail)->next = node;
    *tail = node;
  }
}

void insert_node_back(list **head, list **tail, list *node)
{
  if(!*head)
    *head = *tail = node;
  else
  {
    node->next = *head;
    (*head)->previous = node;
    *head = node;
  }
}

list* search(list *head, list *tail, int key)
{
  for(head, tail; head != tail; head = head->next, tail = tail->previous)
  {
    if(head->key == key)
      return head;
    if(tail->key == key)
      return tail;
  }
  return NULL;
}

void remove_node(list **head, list **tail, int key)
{
  if((*head)->key == key)
  {
    list *tmp = *head;
    *head = (*head)->next;
    free(tmp);
    (*head)->previous = NULL;
    return;
  }
  if((*tail)->key == key)
  {
    list *tmp = *tail;
    *tail = (*tail)->previous;
    free(tmp);
    (*tail)->next = NULL;
    return;
  }
  for(list *tmp_head = *head, *tmp_tail = *tail; tmp_head != tmp_tail; tmp_head = tmp_head->next, tmp_tail = tmp_tail->previous)
  {
    if(tmp_head->key == key)
    {
      list *previous = tmp_head->previous, *next = tmp_head->next;
      previous->next = next;
      next->previous = previous;
      free(tmp_head);
      return;
    }
    if(tmp_tail->key == key)
    {
      list *next = tmp_tail->next, *previous = tmp_tail->previous;
      previous->next = next;
      next->previous = previous;
      free(tmp_tail);
      return;
    }
  }
}

void printf_list(list *head)
{
  for(head; head; head = head->next)
    printf("%d ", head->key);
  printf("\n");
}

void printf_list_reverse(list *tail)
{
  for(tail; tail; tail = tail->previous)
    printf("%d ", tail->key);
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