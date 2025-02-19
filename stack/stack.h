#ifndef STACK_H
#define STACK_H

typedef struct stack_node_t
{
    int data;
    struct stack_node_t *next;
} stack_node_t;

typedef struct
{
    stack_node_t *top;
    size_t length;
} Stack;

void stack_init(Stack *stack);
bool stack_empty(Stack *stack);
void stack_free(Stack *stack);
void stack_pop(Stack *stack);
void stack_push(Stack *stack, int data);
int stack_top(Stack *stack);

#endif
