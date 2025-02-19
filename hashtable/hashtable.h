#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

typedef struct htable_node
{
    uint64_t key;
    int value;
    struct htable_node *next;
} htable_node_t;

typedef struct
{
    size_t num_buckets;
    size_t num_elements;
    htable_node_t **buckets;
} htable_t;

void htable_delete(htable_t *htable, uint64_t key);
void htable_free(htable_t *htable);
void htable_init(htable_t* htable);
void htable_insert(htable_t *htable, uint64_t key, int value);
int htable_get(htable_t *htable, uint64_t key);
void htable_delete(htable_t *htable, uint64_t key);

#endif