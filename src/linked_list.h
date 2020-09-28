#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "utility.h"

typedef struct node {
    int starting_address;
    int size;
    char* content;
    struct node *next;
} Node;

typedef struct list {
    struct node* head;
} List;

#endif