/*
  Code written by Felipe Fraxe Filho
  Just for learning
*/

#include "avl.h"


static inline int max(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

static avl_node_t *node_alloc(int key)
{
    avl_node_t *node = malloc(sizeof(avl_node_t));
    node->key = key;
    node->height = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

static void update_height(avl_node_t *node)
{
    if (node == nullptr)
        return;
    int left_height = (node->left != nullptr) ? node->left->height : -1;
    int right_height = (node->right != nullptr) ? node->right->height : -1;
    node->height = 1 + max(left_height, right_height);
}

static avl_node_t *right_rotation(avl_node_t *node)
{
    avl_node_t *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    update_height(node);
    update_height(tmp);
    return tmp;
}

static avl_node_t *left_rotation(avl_node_t *node)
{
    avl_node_t *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    update_height(node);
    update_height(tmp);
    return tmp;
}

static inline int balance_factor(avl_node_t *node)
{
    if (node == nullptr)
        return 0;
    int left_height = (node->left != nullptr) ? node->left->height : -1;
    int right_height = (node->right != nullptr) ? node->right->height : -1;
    return left_height - right_height;
}

static avl_node_t *balance(avl_node_t *node)
{
    int factor = balance_factor(node);
    if (factor > 1)
    {
        if(balance_factor(node->left) <= 0)
            node->left = left_rotation(node->left);
        node = right_rotation(node);
    }
    else if (factor < -1)
    {
        if(balance_factor(node->right) >= 0)
            node->right = right_rotation(node->right);
        node = left_rotation(node);
    }
    update_height(node);
    return node;
}

static avl_node_t *insert(avl_node_t *node, int key)
{
    if (node == nullptr)
        return node_alloc(key);

    if (node->key == key)
    {
        printf("Key %d already exists in the tree.\n", key);
        return node;
    }

    if (key > node->key)
        node->right = insert(node->right, key);
    else
        node->left = insert(node->left, key);
    node = balance(node);

    return node;
}

static inline avl_node_t *min_node(avl_node_t *node)
{
    while (node->left)
        node = node->left;
    return node;
}

static avl_node_t *remove_node(avl_node_t *node, int key)
{
    if (node == nullptr)
        return node;

    avl_node_t *right = node->right;
    avl_node_t *left = node->left;
    if (key == node->key)
    {
        if (right != nullptr && left != nullptr)
        {
            node->key = min_node(right)->key;
            node->right = remove_node(right, node->key);
        }
        else
        {
            free(node);
            if (right == left)
                return nullptr;
            if (right == nullptr)
                return left;
            return right;
        }
    }
    else if (key > node->key)
        node->right = remove_node(right, key);
    else
        node->left = remove_node(left, key);

    node = balance(node);
    return node;
}

static void dealloc(avl_node_t *node)
{
    if (node == nullptr)
        return;

    dealloc(node->left);
    dealloc(node->right);
    free(node);
}

bool avl_empty(avl_tree_t *tree)
{
    return tree->root == nullptr;
}

void avl_init(avl_tree_t *tree)
{
    tree->root = nullptr;
}

void avl_insert(avl_tree_t *tree, int key)
{
    tree->root = insert(tree->root, key);
}

int avl_get(avl_tree_t *tree, int key)
{
    avl_node_t *curr = tree->root;
    while (curr != nullptr)
    {
        if(curr->key == key)
            return curr->key;
        curr = key > curr->key ? curr->right : curr->left;
    }
    return INT_MIN;
}

void avl_remove(avl_tree_t *tree, int key)
{
    tree->root = remove_node(tree->root, key);
}

void avl_free(avl_tree_t *tree)
{
    dealloc(tree->root);
    tree->root = nullptr;
}

static void print_tree(avl_node_t *node)
{
    if (node == nullptr)
        return;

    print_tree(node->left);
    printf("%d\n", node->key);
    print_tree(node->right);
}

void avl_print_tree(avl_tree_t *tree)
{
    print_tree(tree->root);
}
