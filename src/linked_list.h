#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "utility.h"

typedef struct node {
    void* starting_address;
    int size;
    char* content;
    struct node *next;
} Node;

typedef struct list {
    struct node* head;
} List;

Node* create_node(void* starting_address, int size, char* content);
Boolean add_to_list(List *list, Node *node, Boolean add_to_end);
List* create_list();

#endif