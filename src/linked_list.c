#include "linked_list.h"

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    if(list == NULL) {
        printf("\n List creation failed \n");
        return NULL;
    }

    list -> head = NULL;
    list -> count = 0;

    return list;
}

Boolean add_to_list(List* list, Node* node, Boolean add_to_end) {
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
    /*
    if(list -> head != NULL) {
        printf("ADDING TO HEAD: %s\n", list -> head -> content);
    }
    */
    
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
    list -> count = list -> count + 1;
    return TRUE;
}

List* remove_at_index(List* list, Node* node, int index) {
    Node* pointer = NULL;
    Node* previous = NULL;
    Node* remove = NULL;
    int i = 0;

    pointer = list -> head;
    while(pointer != NULL) {
        if(i == index) {
            remove = pointer;
            if(previous == NULL) {
                list -> head = pointer -> next;
            }
            else {
                previous -> next = pointer -> next;
            }
            free(remove);
            list -> count = list -> count - 1;
            break;
        }
        previous = pointer;
        pointer = pointer -> next;
        i++;
    }
    return list;
}

Node* create_node(void* start_address, void* end_address, int size, char* content) {
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        printf("\n Node creation failed \n");
        return NULL;
    }
    node -> start_address = start_address;
    node -> end_address = end_address;
    node -> size = size;
    node -> content = content;
    node -> next = NULL;

    return node;
}

void print_list(List* list) {
    Node* print_pointer;

    print_pointer = list -> head;
    while(print_pointer != NULL) {
        printf(
            "Start add: %p | End add: %p | Content: %s | Size: %d\n", 
            print_pointer -> start_address,
            print_pointer -> end_address,
            print_pointer -> content,
            print_pointer -> size
        );
        print_pointer = print_pointer -> next;
    }
}
