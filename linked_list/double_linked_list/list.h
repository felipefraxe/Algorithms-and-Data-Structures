#ifndef LIST_H
#define LIST_H

// prototypes for linked lists operations and struct definition
typedef struct ListNode
{
    int key;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct List
{
    ListNode *head;
    ListNode *tail;
    unsigned int length;

    void(*clear)(struct List *);
    bool(*empty)(struct List *);
    ListNode *(*get)(struct List *, int key);
    void(*pop_back)(struct List *);
    void(*pop_front)(struct List *);
    void(*print)(struct List *);
    void(*push_back)(struct List *, ListNode *);
    void(*push_front)(struct List *, ListNode *);
    void(*remove)(struct List *, int key);
    void(*reverse)(struct List *);
    void(*sort)(struct List *);
} List;

List list_init(void);

ListNode *list_create_node(int key);
void list_clear(List *self);
bool list_empty(List *self);
ListNode *list_get(List *self, int key);
void list_pop_back(List *self);
void list_pop_front(List *self);
void list_print(List *self);
void list_push_back(List *self, ListNode *node);
void list_push_front(List *self, ListNode *node);
void list_remove(List *self, int key);
void list_reverse(List *self);
void list_sort(List *self);

void _list_remove_node(ListNode *node);

#endif