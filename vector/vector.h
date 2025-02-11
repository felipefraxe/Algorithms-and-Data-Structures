#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_t
{
    int *data;
    size_t length;
    size_t capacity;
} vector_t;

void vector_init(vector_t *vec);
void vector_free(vector_t *vec);

int vector_at(vector_t *vec, size_t pos);
bool vector_empty(vector_t *vec);
void vector_fill(vector_t *vec, int value);
void vector_remove_at(vector_t *vec, size_t pos);
void vector_set(vector_t *vec, size_t pos, int value);
void vector_shrink_to_fit(vector_t *vec);
void vector_push_back(vector_t *vec, int value);
void vector_reserve(vector_t *vec, size_t capacity);

#endif