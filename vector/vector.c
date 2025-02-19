#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void vector_free(vector_t *vec)
{
    free(vec->data);
    vec->data = nullptr;
    vec->length = 0;
    vec->capacity = 0;
}

void vector_init(vector_t *vec)
{
    vec->capacity = 16;
    vec->length = 0;
    vec->data = malloc(sizeof(*vec->data) * vec->capacity);
}

int vector_at(vector_t *vec, size_t pos)
{
    if (pos >= vec->length)
        return INT_MIN;
    return vec->data[pos];
}

bool vector_empty(vector_t *vec)
{
    return vec->length == 0;
}

void vector_fill(vector_t *vec, int value)
{
    for (size_t i = 0; i < vec->length; i++)
        vec->data[i] = value;
}

void vector_remove_at(vector_t *vec, size_t pos)
{
    if (pos >= vec->length)
        return;

    vec->length--;
    if (pos < vec->length - 1)
        memmove(&vec->data[pos], &vec->data[pos + 1], (vec->length - pos) * sizeof(*vec->data));
}

void vector_set(vector_t *vec, size_t pos, int value)
{
    if (pos < vec->length)
        vec->data[pos] = value;
}

void vector_shrink_to_fit(vector_t *vec)
{
    vec->capacity = vec->length;
    vec->data = realloc(vec->data, vec->capacity * sizeof(*vec->data));
}

void vector_push_back(vector_t *vec, int value)
{
    if (vec->length == vec->capacity)
    {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, sizeof(*vec->data) * vec->capacity);
    }
    vec->data[vec->length] = value;
    vec->length++;
}

void vector_reserve(vector_t *vec, size_t capacity)
{
    if (capacity > vec->capacity)
    {
        vec->capacity = capacity;
        vec->data = realloc(vec->data, sizeof(*vec->data) * vec->capacity);
    }
}