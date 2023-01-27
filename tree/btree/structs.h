#ifndef STRUCTS_H
#define STRUCTS_H

#define ORDER 7
#define MIN (ORDER - 1) / 2

typedef struct
{
    unsigned int key;
}
MyData;

// Btree Type
typedef struct Btree
{
    int num_keys;
    MyData data[ORDER + 1];
    int (*is_leaf)(struct Btree *this);
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