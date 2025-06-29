#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    int *data;
    size_t length;
    size_t capacity;
} vector_t;

// Basic Operations
bool vector_empty(vector_t *vec);
void vector_free(vector_t *vec);
void vector_init(vector_t *vec);

// Insert
void vector_fill(vector_t *vec, int value);
void vector_push_back(vector_t *vec, int value);
void vector_set(vector_t *vec, size_t pos, int value);

// Delete
void vector_remove_at(vector_t *vec, size_t pos);

// Search
int vector_at(vector_t *vec, size_t pos);

// Utils
void vector_shrink_to_fit(vector_t *vec);
void vector_reserve(vector_t *vec, size_t capacity);

#endif