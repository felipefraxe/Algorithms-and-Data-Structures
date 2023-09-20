#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>


typedef struct HTable_Data
{
    char *key;
    char *value;
}
HTable_Data;


typedef struct HTable_Node
{
    HTable_Data *data;
    struct HTable_Node *next;
}
HTable_Node;


int cmputf8(const void *wcs1, const void *wcs2);
size_t wcshash(wchar_t *key, size_t length);
size_t strhash(char *key, size_t length);
HTable_Data *htable_create_data(char *key, char *value);
void htable_deallocate_data(HTable_Data *data);
HTable_Node *htable_create_node(HTable_Data *data);
HTable_Node **htable_create(size_t length);
void htable_insert_node(HTable_Node **hashtable, size_t length, HTable_Node *node, size_t (*hash)(const void *, size_t));
void htable_delete_node(HTable_Node **hashtable, size_t length, void *key, int (*cmp)(const void *, const void *), size_t (*hash)(const void *, size_t));
HTable_Data *htable_search_node(HTable_Node **hash_table, size_t length, void *key, int (*cmp)(const void *, const void *), size_t (*hash)(const void *, size_t));
void htable_deallocate(HTable_Node **hash_table, size_t length);

#endif