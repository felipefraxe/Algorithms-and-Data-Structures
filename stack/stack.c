#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack stack_init(void)
{
    return (Stack){
        .top = nullptr,
        .length = 0,

        .clear = stack_clear,
        .empty = stack_empty,
        .pop = stack_pop,
        .push = stack_push};
}

StackNode *stack_create_node(int key)
{
    StackNode *node = malloc(sizeof(StackNode));
    if (node == nullptr)
    {
        fprintf(stderr, "Could not allocate memory for node. Something went wrong\n");
        return nullptr;
    }
    node->key = key;
    node->next = nullptr;
    return node;
}

void stack_clear(Stack *self)
{
    while (!stack_empty(self))
        stack_pop(self);
    self->length = 0;
}

bool stack_empty(Stack *self)
{
    return self->length == 0;
}

void stack_pop(Stack *self)
{
    StackNode *tmp = self->top;
    self->top = tmp->next;

    free(tmp);

    self->length--;
}

void stack_push(Stack *self, StackNode *node)
{
    if (self->top != nullptr)
        node->next = self->top;
    self->top = node;

    self->length++;
}

