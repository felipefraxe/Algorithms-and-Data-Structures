/*
  Code written by Felipe Fraxe
  Just for learning
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "btree.h"

int main(void)
{
    Btree *root = NULL;
    list *stack = NULL;

    int num[] = { 30, 20, 40, 50, 2, 10, 18, 7, 15, 16, 25, 60, 1, 70, 55, 66, 14, 51, 92, 115, 17, 134, 23, 565,
        19, 42, 37, 58, 32, 47, 214, 354, 666, 789, 74, 539, 452, 810, 1024, 1120, 701, 234, 568, 982, 703, 459, 327,
        882, 694, 702, 557, 210, 212, 387, 10534, 862, 303, 549, 100, 22, 21, 27, 9, 6 };
    int size = sizeof(num) / sizeof(num[0]);
    MyData datas[size];

    for(int i = 0; i < size; i++)
    {
        MyData d = { num[i] };
        datas[i] = d;
    }

    for(int i = 0; i < size; i++)
        insert_key(&root, datas[i], &stack);
    for(int i = 0; i < size; i++)
        remove_key(&root, datas[i], &stack);
    printf_tree(root);
    deallocate(root);
    return EXIT_SUCCESS;
}

int is_leaf(Btree *this)
{
    return this->children[0] == NULL;
}

Btree* create_node()
{
    Btree *node = calloc(1, sizeof(Btree));
    if(node == NULL)
    {
        perror("Failed to allocate memory for new node. Exiting...\n");
        exit(EXIT_FAILURE);
    }
    node->is_leaf = is_leaf;
    return node;
}

int cmpMyData(const void *data1, const void *data2)
{
    return (*(MyData *)data1).key - (*(MyData *)data2).key;
}

int binsearch(void *array, size_t size, int low, int high, void *key, int (* cmp)(const void *, const void *))
{
    int mid = low + (high - low) / 2;
    while(low <= high)
    {
        if(cmp(key, array + (mid * size)) > 0)
            low = mid + 1;
        else if(cmp(key,array + (mid * size)) < 0)
            high = mid - 1;
        else
            return mid;
        mid = low + (high - low) / 2;
    }
    return mid;
}

void insert_sorted(Btree *node, int index, MyData new_data)
{
    for(int i = node->num_keys; i > index; i--)
    {
        node->data[i] = node->data[i-1];
        node->children[i+1] = node->children[i];
    }
    node->data[index] = new_data;
}

void copy_array(Btree *source, Btree *dest, int start, int end)
{
    for(int i = start; i < end; i++)
    {
        dest->data[i-start] = source->data[i];
        dest->children[i-start] = source->children[i];
    }
    dest->children[end-start] = source->children[end];
}


void split_node(Btree **root, list **parent, MyData new_data, int mid)
{
    int index;

    Btree *left = create_node();
    copy_array(*root, left, 0, mid);
    left->num_keys = mid;

    Btree *right = create_node();
    copy_array(*root, right, mid+1, ORDER);
    right->num_keys = ORDER % 2 == 0 ? mid + 1 : mid;

    if(*parent != NULL)
    {
        free(*root);
        root = (*parent)->root;
        pull(parent);
    }
    else
        (*root)->num_keys = 0;

    index = binsearch((*root)->data, sizeof(MyData), 0, (*root)->num_keys - 1, &new_data, cmpMyData);
    insert_sorted(*root, index, new_data);
    (*root)->children[index] = left;
    (*root)->children[index+1] = right;

    if((*root)->num_keys < ORDER-1)
        (*root)->num_keys++;
    else
    {
        mid = (*root)->num_keys / 2;
        new_data = (*root)->data[mid];
        split_node(root, parent, new_data, mid);
    }
}

void insert_key(Btree **root, MyData new_data, list **parent)
{
    int index, mid;

    if(*root == NULL && *parent == NULL)
    {
        *root = create_node();
        (*root)->data[0] = new_data;
        (*root)->num_keys++;
        return;
    }
    index = binsearch((*root)->data, sizeof(MyData), 0, (*root)->num_keys - 1, &new_data, cmpMyData);
    if(index < (*root)->num_keys && cmpMyData(&(*root)->data[index], &new_data) == 0)
    {
        printf("Reapeated key %d!\n", new_data.key);
        return;
    }

    if((*root)->is_leaf(*root))
    {
        insert_sorted(*root, index, new_data);
        if((*root)->num_keys < ORDER-1)
            (*root)->num_keys++;
        else
        {
            mid = (*root)->num_keys / 2;
            new_data = (*root)->data[mid];
            split_node(root, parent, new_data, mid);
        }
        return;
    }
    push(parent, new_node(root));
    insert_key(&(*root)->children[index], new_data, parent);
    pull(parent);
}

void remove_sorted(Btree *node, int index)
{
    for(int i = index; i < node->num_keys; i++)
    {
        node->data[i] = node->data[i+1];
        node->children[i] = node->children[i+1];
    }
    node->children[node->num_keys] = NULL;
    node->num_keys--;
}

MyData find_max_in_min_child(Btree *node)
{
    while(node->children[node->num_keys])
        node = node->children[node->num_keys];
    return node->data[node->num_keys - 1];
}

MyData find_min_in_max_child(Btree *node)
{
    while(node->children[0])
        node = node->children[0];
    return node->data[0];
}

void left_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
    root->data[root->num_keys++] = parent->data[parent_index];
    root->children[root->num_keys] = sibling->children[0];
    parent->data[parent_index] = sibling->data[0];
    remove_sorted(sibling, 0);
}

void right_rotation(Btree *root, Btree *sibling, Btree *parent, int parent_index)
{
    root->num_keys++;
    insert_sorted(root, 0, parent->data[parent_index]);
    parent->data[parent_index] = sibling->data[sibling->num_keys-1];
    root->children[0] = sibling->children[sibling->num_keys];
    sibling->children[sibling->num_keys] = NULL;
    sibling->num_keys--;
}

int find_child(Btree *root, Btree *child)
{
    int low = 0, high = root->num_keys + 1;
    int mid = high / 2;
    while(low <= high)
    {
        if(root->children[mid] == child)
            return mid;
        if(root->children[mid]->data[0].key < child->data[0].key)
            low = mid + 1;
        else
            high = mid - 1;
        mid = (high + low) / 2;
    }
    return -1;
}

void adjust_root(Btree *root, list **parent)
{
    Btree **parent_root = (*parent)->root, *sibling;
    int parent_index = find_child(*parent_root, root);
    pull(parent);

    if(parent_index == 0)
    {
        sibling = (*parent_root)->children[parent_index+1];
        if(sibling->num_keys > MIN)
            left_rotation(root, sibling, *parent_root, parent_index);
        else
            merge_node(parent_root, sibling, root, parent_index, parent);
        return;
    }
    sibling = (*parent_root)->children[parent_index-1];
    if(sibling->num_keys > MIN)
        right_rotation(root, sibling, *parent_root, parent_index-1);
    else if(parent_index == (*parent_root)->num_keys)
        merge_node(parent_root, sibling, root, parent_index, parent);
}

void move_array(Btree *source, Btree *dest, int end)
{
    for(int i = 0; i < end; i++)
    {
        dest->data[dest->num_keys] = source->data[i];
        dest->children[dest->num_keys] = source->children[i];
        dest->num_keys++;
    }
    dest->children[dest->num_keys] = source->children[end];
    free(source);
    source = NULL;
}

void merge_node(Btree **parent_root, Btree *sibling, Btree *root, int parent_index, list **parent)
{
    if(parent_index > 0 && (*parent_root)->children[parent_index-1] == sibling)
    {
        sibling->data[sibling->num_keys++] = (*parent_root)->data[parent_index-1];
        move_array(root, sibling, root->num_keys);
        remove_sorted(*parent_root, parent_index-1);
        (*parent_root)->children[parent_index-1] = sibling;
    }
    else
    {
        root->data[root->num_keys++] = (*parent_root)->data[parent_index];
        move_array(sibling, root, sibling->num_keys);
        remove_sorted(*parent_root, parent_index);
        (*parent_root)->children[parent_index] = root;
    }

    if(*parent == NULL && (*parent_root)->num_keys == 0)
    {
        free(*parent_root);
        *parent_root = sibling != NULL ? sibling : root;
    }
    else if(*parent != NULL && (*parent_root)->num_keys < MIN)
        adjust_root(*parent_root, parent);
}

void remove_key(Btree **root, MyData rmv_data, list **parent)
{
    int index, parent_index;
    Btree *sibling, **parent_address;

    if(*root == NULL)
      return;

    index = binsearch((*root)->data, sizeof(MyData), 0, (*root)->num_keys - 1, &rmv_data, cmpMyData);
    if(index < (*root)->num_keys && cmpMyData(&(*root)->data[index], &rmv_data) == 0)
    {
        if((*root)->is_leaf(*root))
        {
            remove_sorted(*root, index);
            if((*root)->num_keys >= MIN || *parent == NULL)
            {
                if((*root)->num_keys == 0)
                {
                    free(*root);
                    *root = NULL; 
                }
                return;
            }
            parent_address = (*parent)->root;
            pull(parent);
            parent_index = find_child(*parent_address, *root);
            if(parent_index > 0)
            {
                sibling = (*parent_address)->children[parent_index-1];
                if(sibling->num_keys > MIN)
                {
                    right_rotation(*root, sibling, *parent_address, parent_index-1);
                    return;
                }
                if(parent_index == (*parent_address)->num_keys)
                {
                    merge_node(parent_address, sibling, *root, parent_index, parent);
                    return;
                }
            }
            sibling = (*parent_address)->children[parent_index+1];
            if(sibling->num_keys > MIN)
                left_rotation(*root, sibling, *parent_address, parent_index);
            else
                merge_node(parent_address, sibling, *root, parent_index, parent);
            return;
        }
        else
        {
            if((*root)->children[index]->num_keys > MIN)
            {
                rmv_data = find_max_in_min_child((*root)->children[index]);
                (*root)->data[index] = rmv_data;
            }
            else
            {
                rmv_data = find_min_in_max_child((*root)->children[index + 1]);
                (*root)->data[index] = rmv_data;
                index++;
            }
        }
    }
    push(parent, new_node(root));
    remove_key(&(*root)->children[index], rmv_data, parent);
    pull(parent);
}

Btree* search(Btree *root, MyData data)
{
    while(root != NULL)
    {
        int index = binsearch(root->data, sizeof(MyData), 0, root->num_keys - 1, &data, cmpMyData);
        if(cmpMyData(&root->data[index], &data) == 0)
            return root;
        root = root->children[index];
    }
    return root;
}

void printf_tree(Btree *node)
{
    if(node == NULL)
        return;

    int i = 0;
    printf_tree(node->children[i]);
    while(i < node->num_keys)
    {
        printf("%d\n", node->data[i].key);
        printf_tree(node->children[++i]);
    }
}

void deallocate(Btree *node)
{
    if(node == NULL)
        return;

    int children_size = node->num_keys + 1;
    for(int i = 0; !node->is_leaf(node) && i < children_size; i++)
        deallocate(node->children[i]);
    free(node);
}