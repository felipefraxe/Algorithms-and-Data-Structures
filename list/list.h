#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} list_node_t;

typedef struct
{
    list_node_t *sentinel;
    size_t length;
} list_t;

// Basic Operations
bool list_empty(list_t *list);
void list_free(list_t *list);
void list_init(list_t *list);
void list_remove_all(list_t *list);

// Insert
void list_insert_at(list_t *list, int data, size_t pos);
void list_push_back(list_t *list, int data);
void list_push_front(list_t *list, int data);

// Delete
void list_remove_at(list_t *list, size_t pos);
void list_pop_back(list_t *list);
void list_pop_front(list_t *list);
void list_remove_data(list_t *list, int data);

// Search
int list_back(list_t *list);
int list_data_at(list_t *list, size_t pos);
int list_front(list_t *list);

// Utils
void list_print(list_t *list);
void list_reverse(list_t *list);

#endif