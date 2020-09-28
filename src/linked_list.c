#include "linked_list.h"

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    if(list == NULL) {
        printf("\n List creation failed \n");
        return NULL;
    }

    list -> head = NULL;

    return list;
}

Boolean add_to_list(List *list, Node *node, Boolean add_to_end) {
    Node* pointer = NULL;
    /* If a list does not exist, a node cannot be added to it */
    if(list == NULL) {
        printf("\n List does not exist \n");
        return FALSE;
    }
    /* If a node does not exist, it cannot be added to the list */
    if(node == NULL) {
        printf("\n Node does not exist \n");
        return FALSE;
    }
    /* If this is the first item being added to the list */
    if(list -> head == NULL) {
        list -> head = node;
    }
    else {
        if(add_to_end) {
           pointer = list -> head;
            while(pointer != NULL) {
                if(pointer -> next == NULL) {
                    pointer -> next = node;
                    break;
                }
                pointer = pointer -> next;
            }
        }
        else {
            node -> next = list -> head;
            list -> head = node;   
        }        
    }
    return TRUE;
}

Node* create_node(int starting_address, int size, char* content) {
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        printf("\n Node creation failed \n");
        return NULL;
    }
    node -> starting_address = starting_address;
    node -> size = size;
    node -> content = content;
    node -> next = NULL;

    return node;
}
