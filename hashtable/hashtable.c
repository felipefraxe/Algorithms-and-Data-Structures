#include "hashtable.h"


size_t wcshash(wchar_t *key, size_t length)
{
    size_t index = 5381;
    wint_t c;
    while ((c = *key++) != L'\0')
        index = (index * 33) + c;
    return index % length;
}


size_t strhash(char *key, size_t length)
{
    size_t index = 5381;
    int c;
    while ((c = *key++) != '\0')
        index = (index * 33) + c;
    return index % length;
}


HTable_Node *htable_create_data(char *key, char *value)
{
    HTable_Data *data = malloc(sizeof(HTable_Data));
    if(data == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(EXIT_FAILURE);
    }

    data->key = malloc((strlen(key) + 1));
    data->value = malloc((strlen(value) + 1));
    if(data->key == NULL || data->value == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(data->key, key);
    strcpy(data->value, value);

    return data;
}


HTable_Node *htable_create_node(HTable_Node *data)
{
    HTable_Node *node = malloc(sizeof(HTable_Node));
    if(node == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->next = NULL;
    return node;
}


HTable_Node **htable_create(size_t length)
{
    HTable_Node **hashtable = malloc(sizeof(HTable_Node) * length);
    if(hashtable == NULL)
    {
        fprintf(stderr, "Mem allocation error\n");
        exit(EXIT_FAILURE);
    }
    return hashtable;
}


void htable_insert_node(HTable_Node **hashtable, size_t length, HTable_Node *node, size_t (*hash)(const void *, size_t))
{
    size_t index = hash(node->data->key, length);
    if(hashtable[index] != NULL)
        node->next = hashtable[index];
    hashtable[index] = node;
}


void htable_delete_node(HTable_Node **hashtable, size_t length, void *key, int (*cmp)(const void *, const void *), size_t (*hash)(const void *, size_t))
{
    size_t index = hash(key, length);
    HTable_Node *tmp = hashtable[index], *previous = NULL;
    while(tmp != NULL)
    {
        if(cmp(tmp->data->key, key) == 0)
        {
            free(tmp->data->key);
            free(tmp->data->value);
            free(tmp->data);
            if(previous != NULL)
                previous->next = tmp->next;
            else
                hashtable[index] = tmp->next;
            free(tmp);
            return;
        }
        previous = tmp;
        tmp = tmp->next;
    }
}


HTable_Node *htable_search_node(HTable_Node **hash_table, size_t length, void *key, int (*cmp)(const void *, const void *), size_t (*hash)(const void *, size_t))
{
    size_t index = hash(key, length);
    for(HTable_Node *tmp = hash_table[index]; tmp != NULL; tmp = tmp->next)
    {
        if(cmp(tmp->data->key, key) == 0)
            return tmp->data;
    }
    return NULL;
}


void htable_deallocate(HTable_Node **hashtable, size_t length)
{
    for(int i = 0; i < length; i++)
    {
        while(hashtable[i] != NULL)
        {
            HTable_Node *tmp = hashtable[i]->next;
            free(hashtable[i]->data->key);
            free(hashtable[i]->data->value);
            free(hashtable[i]->data);
            free(hashtable[i]);
            hashtable[i] = tmp;
        }
    }
}