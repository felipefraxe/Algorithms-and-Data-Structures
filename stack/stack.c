#include <stdlib.h>

#include "stack.h"

static stack_node_t *node_alloc(int data)
{
    stack_node_t *node = malloc(sizeof(stack_node_t));
    if (node == nullptr)
        return nullptr;
    node->data = data;
    node->next = nullptr;
    return node;
}

void stack_init(Stack *stack)
{
    stack->top = nullptr;
    stack->length = 0;
}

void stack_free(Stack *stack)
{
    while (!stack_empty(stack))
        stack_pop(stack);
    stack->length = 0;
}

inline bool stack_empty(Stack *stack)
{
    return stack->length == 0;
}

void stack_pop(Stack *stack)
{
    if (stack_empty(stack))
        return;

    stack_node_t *tmp = stack->top;
    stack->top = tmp->next;
    free(tmp);
    stack->length--;
}

void stack_push(Stack *stack, int data)
{
    stack_node_t *node = node_alloc(data);
    if (stack->top != nullptr)
        node->next = stack->top;
    stack->top = node;
    stack->length++;
}

int stack_top(Stack *stack)
{
    if (stack->top == nullptr)
        return INT_MIN;
    return stack->top->data;
}