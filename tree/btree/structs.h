#ifndef STRUCTS_H
#define STRUCTS_H

#define ORDER 7
#define MIN (ORDER - 1) / 2

// Btree Type
typedef struct Btree
{
    int num_keys;
    int keys[ORDER + 1];
    struct Btree *children[ORDER + 1];
}
Btree;

// List type
typedef struct list
{
    Btree **root;
    struct list *next;
}
list;

#endif