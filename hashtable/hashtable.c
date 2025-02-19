#include <limits.h>
#include <stdlib.h>

#include "hashtable.h"

static bool is_prime(size_t num) {
    if (num < 2)
        return false;

    if (num % 2 == 0)
        return num == 2;

    for (size_t i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

static size_t next_prime(size_t num)
{
    while (!is_prime(num))
        num++;
    return num;
}

static htable_node_t *node_alloc(uint64_t key, int value)
{
    htable_node_t *node = malloc(sizeof(htable_node_t));

    node->key = key;
    node->value = value;
    node->next = nullptr;

    return node;
}

uint64_t murmurhash3_64(const void *key, size_t len, uint32_t seed)
{
    const uint8_t *data = (const uint8_t *) key;
    const int nblocks = len / 8;
    uint64_t h1 = seed;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    const uint64_t *blocks = (const uint64_t *)(data);
    for (int i = 0; i < nblocks; i++)
    {
        uint64_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 31) | (k1 >> 33);
        k1 *= c2;
        h1 ^= k1;

        h1 = (h1 << 27) | (h1 >> 37);
        h1 = h1 * 5 + 0x52dce729;
    }

    const uint8_t *tail = (const uint8_t *)(data + nblocks * 8);
    uint64_t k1 = 0;

    switch (len & 7)
    {
    case 7:
        k1 ^= (uint64_t)tail[6] << 48;
    case 6:
        k1 ^= (uint64_t)tail[5] << 40;
    case 5:
        k1 ^= (uint64_t)tail[4] << 32;
    case 4:
        k1 ^= (uint64_t)tail[3] << 24;
    case 3:
        k1 ^= (uint64_t)tail[2] << 16;
    case 2:
        k1 ^= (uint64_t)tail[1] << 8;
    case 1:
        k1 ^= (uint64_t)tail[0];
        k1 *= c1;
        k1 = (k1 << 31) | (k1 >> 33);
        k1 *= c2;
        h1 ^= k1;
    }

    h1 ^= len;
    h1 ^= h1 >> 33;
    h1 *= 0xff51afd7ed558ccdULL;
    h1 ^= h1 >> 33;
    h1 *= 0xc4ceb9fe1a85ec53ULL;
    h1 ^= h1 >> 33;

    return h1;
}

static size_t hash(uint64_t key, size_t length)
{
    uint64_t hash_value = murmurhash3_64(&key, sizeof(key), 0x9747b28c);
    return hash_value % length;
}

static void resize(htable_t *htable)
{
    size_t new_size = next_prime(htable->num_buckets * 1.5);
    htable_node_t **new_buckets = calloc(new_size, sizeof(htable_node_t *));

    for (size_t i = 0; i < htable->num_buckets; i++)
    {
        htable_node_t *node = htable->buckets[i];
        while (node != nullptr)
        {
            htable_node_t *next = node->next;

            size_t new_bucket = hash(node->key, new_size);
            node->next = new_buckets[new_bucket];
            new_buckets[new_bucket] = node;

            node = next;
        }
    }

    free(htable->buckets);

    htable->buckets = new_buckets;
    htable->num_buckets = new_size;
}


void htable_init(htable_t *htable)
{
    htable->num_buckets = 17;
    htable->num_elements = 0;
    htable->buckets = calloc(htable->num_buckets, sizeof(htable_node_t *));
}

void htable_free(htable_t *htable)
{
    for (size_t i = 0; i < htable->num_buckets; i++)
    {
        while (htable->buckets[i] != nullptr)
        {
            htable_node_t *tmp = htable->buckets[i]->next;
            free(htable->buckets[i]);
            htable->buckets[i] = tmp;
        }
    }
    free(htable->buckets);
    htable->num_elements = 0;
    htable->num_buckets = 0;
}

void htable_insert(htable_t *htable, uint64_t key, int value)
{
    size_t bucket = hash(key, htable->num_buckets);
    for (htable_node_t *tmp = htable->buckets[bucket]; tmp != nullptr; tmp = tmp->next)
    {
        if (key == tmp->key)
        {
            tmp->value = value;
            return;
        }
    }

    htable_node_t *node = node_alloc(key, value);

    node->next = htable->buckets[bucket];
    htable->buckets[bucket] = node;
    htable->num_elements++;

    if (htable->num_elements >= htable->num_buckets * 0.8)
        resize(htable);
}

int htable_get(htable_t *htable, uint64_t key)
{
    size_t bucket = hash(key, htable->num_buckets);
    for (htable_node_t *tmp = htable->buckets[bucket]; tmp != nullptr; tmp = tmp->next)
    {
        if (key == tmp->key)
            return tmp->value;
    }
    return INT_MIN;
}

void htable_delete(htable_t *htable, uint64_t key)
{
    size_t bucket = hash(key, htable->num_buckets);
    htable_node_t *prev = nullptr;
    for (htable_node_t *tmp = htable->buckets[bucket]; tmp != nullptr; tmp = tmp->next)
    {
        if (key == tmp->key)
        {
            if(prev != nullptr)
                prev->next = tmp->next;
            else
                htable->buckets[bucket] = tmp->next;
            free(tmp);
            htable->num_elements--;
            return;
        }
        prev = tmp;
    }
}
