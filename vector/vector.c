#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void vector_free(vector_t *vec)
{
    free(vec->arr);
    vec->arr = nullptr;
    vec->length = 0;
    vec->capacity = 0;
}

void vector_init(vector_t *vec)
{
    vec->arr = malloc(sizeof(int));
    vec->capacity = 1;
    vec->length = 0;
}

int vector_at(vector_t *vec, size_t pos)
{
    if (pos >= vec->length)
        return INT_MIN;
    return vec->arr[pos];
}

bool vector_empty(vector_t *vec)
{
    return vec->length == 0;
}

void vector_fill(vector_t *vec, int value)
{
    for (size_t i = 0; i < vec->length; i++)
        vec->arr[i] = value;
}

void vector_remove_at(vector_t *vec, size_t pos)
{
    if (pos >= vec->length)
        return;
    
    vec->length--;
    memmove(&vec->arr[pos], &vec->arr[pos + 1], (vec->length - pos) * sizeof(*vec->arr));
}

void vector_set(vector_t *vec, size_t pos, int value)
{
    if (pos < vec->length)
        vec->arr[pos] = value;
}

void vector_shrink_to_fit(vector_t *vec)
{
    vec->capacity = vec->length;
    vec->arr = realloc(vec->arr, vec->capacity * sizeof(*vec->arr));
}

void vector_push_back(vector_t *vec, int value)
{
    if (vec->length == vec->capacity)
    {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr, sizeof(*vec->arr) * vec->capacity);
    }
    vec->arr[vec->length] = value;
    vec->length++;
}

void vector_reserve(vector_t *vec, size_t capacity)
{
    if (capacity > vec->capacity)
    {
        vec->capacity = capacity;
        vec->arr = realloc(vec->arr, sizeof(*vec->arr) * vec->capacity);
    }
}