#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "utility.h"

typedef struct node {
    void* start_address;
    void* end_address;
    int size;
    char* content;
    struct node *next;
} Node;

typedef struct list {
    struct node* head;
    int count;
} List;

Node* create_node(void* start_address,  void* end_address, int size, char* content);
Boolean add_to_list(List *list, Node *node, Boolean add_to_end);
List* remove_at_index(List* list, Node* node, int index);
List* remove_node(List* list, Node* node);
Node* split_block(Node* node, int size);
List* create_list();
void print_list(List* list);
#endif