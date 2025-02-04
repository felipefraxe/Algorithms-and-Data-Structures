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
    unsigned int length;
} list_t;

list_t *list_init(void);
void list_destroy(list_t *list);

//void list_clear(list_t *list);
bool list_empty(list_t *list);
//list_node_t *list_get(list_t *list, int key);
//void list_pop_back(list_t *list);
//void list_pop_front(list_t *list);
void list_print(list_t *list);
void list_push_back(list_t *list, int key);
void list_push_front(list_t *list, int key);
//void list_remove(list_t *list, int key);
//void list_reverse(list_t *list);
//void list_sort(list_t *list);

static list_node_t *list_create_node(int key);
//static void list_remove_node(list_node_t *node);

#endif