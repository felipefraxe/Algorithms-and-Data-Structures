#ifndef STACK_H
#define STACK_H

typedef struct StackNode
{
    int key;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
    unsigned int length;

    bool(*empty)(struct Stack *);
    void(*clear)(struct Stack *);
    void(*pop)(struct Stack *);
    void(*push)(struct Stack *, StackNode *);
} Stack;

Stack stack_init(void);
StackNode *stack_create_node(int key);
void stack_clear(Stack *self);
bool stack_empty(Stack *self);
void stack_pop(Stack *self);
void stack_push(Stack *self, StackNode *node);

#endif
