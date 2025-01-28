#include <assert.h>
#include <stdio.h>

#include "list.h"

int main() {
    // Test list initialization
    List list = list_init();
    assert(list.head == nullptr);
    assert(list.tail == nullptr);
    assert(list.length == 0);
    printf("test_list_init passed\n");

    // Test adding elements to the list (push_front and push_back)
    ListNode *node1 = list_create_node(10);
    ListNode *node2 = list_create_node(20);
    ListNode *node3 = list_create_node(30);

    list.push_back(&list, node1);
    list.push_back(&list, node2);
    list.push_front(&list, node3);

    // List should be: 30, 10, 20
    assert(list.head->key == 30);
    assert(list.tail->key == 20);
    assert(list.length == 3);
    printf("test_push_front_and_push_back passed\n");

    // Test removing elements from the list
    list.remove(&list, 20); // Remove middle node
    assert(list.length == 2);
    assert(list.head->key == 30);
    assert(list.tail->key == 10);

    list.remove(&list, 10); // Remove head node
    assert(list.length == 1);
    assert(list.head->key == 30);

    list.remove(&list, 30); // Remove last node
    assert(list.length == 0);
    assert(list.head == nullptr);
    assert(list.tail == nullptr);

    // Test removal from an empty list
    assert(list.length == 0);
    printf("test_list_remove passed\n");

    // Test list reversal
    ListNode *node4 = list_create_node(10);
    ListNode *node5 = list_create_node(20);
    ListNode *node6 = list_create_node(30);

    list.push_back(&list, node4);
    list.push_back(&list, node5);
    list.push_back(&list, node6);

    list.reverse(&list); // List should be: 30, 20, 10
    assert(list.head->key == 30);
    assert(list.tail->key == 10);
    assert(list.length == 3);
    printf("test_list_reverse passed\n");

    // Test list sorting
    ListNode *node7 = list_create_node(50);
    ListNode *node8 = list_create_node(40);
    ListNode *node9 = list_create_node(60);

    list.push_back(&list, node7);
    list.push_back(&list, node8);
    list.push_back(&list, node9);

    list.sort(&list); // List should be sorted: 10, 20, 30, 40, 50, 60
    ListNode *node = list.head;
    assert(node->key == 10);
    node = node->next;
    assert(node->key == 20);
    node = node->next;
    assert(node->key == 30);
    node = node->next;
    assert(node->key == 40);
    node = node->next;
    assert(node->key == 50);
    node = node->next;
    assert(node->key == 60);
    printf("test_list_sort passed\n");

    // Test empty list
    list.clear(&list);
    assert(list.length == 0);
    assert(list.head == nullptr);
    assert(list.tail == nullptr);
    printf("test_empty_list passed\n");

    // Test getting a node by key
    list.push_back(&list, list_create_node(10));
    list.push_back(&list, list_create_node(20));
    list.push_back(&list, list_create_node(30));

    ListNode *found_node = list.get(&list, 20);
    assert(found_node != nullptr);
    assert(found_node->key == 20);

    ListNode *not_found_node = list.get(&list, 100);
    assert(not_found_node == nullptr);

    printf("test_get_node_by_key passed\n");

    return 0;
}