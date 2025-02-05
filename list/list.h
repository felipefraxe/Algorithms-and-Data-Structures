#ifndef LIST_H
#define LIST_H

// prototypes for linked lists operations and struct definition
typedef struct list_node
{
    int key;
    struct list_node *next;
    struct list_node *prev;
} list_node_t;

typedef struct list
{
    list_node_t *sentinel;
    size_t length;
} list_t;

// Basic Operations
bool list_empty(list_t *list);
void list_free(list_t *list);
list_t list_init(void);
void list_remove_all(list_t *list);

// Insert
void list_insert_at(list_t *list, int key, size_t pos);
void list_push_back(list_t *list, int key);
void list_push_front(list_t *list, int key);

// Delete
void list_remove_at(list_t *list, size_t pos);
void list_pop_back(list_t *list);
void list_pop_front(list_t *list);
void list_remove_key(list_t *list, int key);

// Search
int list_key_at(list_t *list, size_t pos);

// Utils
void list_print(list_t *list);

//list_node_t *list_get(list_t *list, int key);
//void list_reverse(list_t *list);
//void list_sort(list_t *list);

//static void list_remove_node(list_node_t *node);

#endif