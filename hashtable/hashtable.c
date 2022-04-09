/*
  Code written by Felipe Fraxe
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 26 * 26

typedef struct Node {
  char *key;
  char *value;
  struct Node *next;
}
Node;

unsigned int hash(char *key);
void add_node(Node *hash_table[], char *key, char *value);
char* search_node(Node *hash_table[], char *key);
Node* create_node(char *key, char *value);
void deallocate_table(Node *hash_table[]);

Node *hash_table[MAX_LENGTH] = {};

int main(void) {
  add_node(hash_table, "Felipe", "Fraxe");
  add_node(hash_table, "epileF", "Filho");
  printf("%s\n", search_node(hash_table, "Felipe"));
  printf("%s\n", search_node(hash_table, "epileF"));
  
  deallocate_table(hash_table);
  return EXIT_SUCCESS;
}

unsigned int hash(char *key)
{
  unsigned int index = 5381;
  int c;
  while((c = *key++) != '\0')
    index = (index * 33) + c;
  return (index % MAX_LENGTH);
}


Node* create_node(char *key, char *value)
{
  Node *node = malloc(sizeof(Node));
  if(!node)
  {
    printf("Could not allocate memory for node\n");
    exit(EXIT_FAILURE);
  }
  node->key = malloc(sizeof(strlen(key)+1));
  strcpy(node->key, key);
  node->value = malloc(sizeof(strlen(value)+1));
  strcpy(node->value, value);
  node->next = NULL;
  return node;
}


void add_node(Node *hash_table[], char *key, char *value)
{
  Node *node = create_node(key, value);
  int index = hash(key); 
  if(hash_table[index])
    node->next = hash_table[index];
  hash_table[index] = node;
}


char* search_node(Node *hash_table[], char *key)
{
  unsigned int index = hash(key);
  Node *tmp = hash_table[index];
  while(tmp)
  {
    if(strcmp(tmp->key, key) == 0)
      return tmp->value;
    tmp = tmp->next;
  }
  return "";
}


void deallocate_table(Node *hash_table[])
{
  for(int i = 0; i < MAX_LENGTH; i++)
  {
    while(hash_table[i])
    {
      Node *tmp = hash_table[i]->next;
      free(hash_table[i]->key);
      free(hash_table[i]->value);
      free(hash_table[i]);
      hash_table[i] = tmp;
    }
  }
}