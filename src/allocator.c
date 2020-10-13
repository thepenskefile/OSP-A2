#include "allocator.h"

int main(int argc, char** argv) {
    const char* file_name;
    const char* strategy;
    const char* output_file_name;
    Allocator* allocator;

    if(argc != NUMBER_ARGUMENTS) {
        fprintf(stderr, "Error! Usage:\n\t%s <data file> <allocator strategy> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    strategy = argv[2];
    output_file_name = argv[3];

    allocator = create_allocator();
    if(strcmp(strategy, FF) == 0) {
        allocator -> strategy = FIRST_FIT;
    }
    else if(strcmp(strategy, BF) == 0) {
        allocator -> strategy = BEST_FIT;
    }
    else if(strcmp(strategy, WF) == 0) {
        allocator -> strategy = WORST_FIT;
    }
        
    srand(time(0));
    
    load_data(file_name, NAMES_TO_READ, allocator);
      
    printf("-----freedMBList-----\n\n");
    print_list(allocator -> freedMBList);
    printf("-----allocMBList-----\n\n");;
    print_list(allocator -> allocMBList);

    printf("\n----------------------\n\n");
    
    printf("Total nodes in freedMBList: %d\n", allocator -> freedMBList -> count);
    printf("Total nodes in allocMBList: %d\n", allocator -> allocMBList -> count);
    printf("Total memory allocated: %d\n", allocator -> total_allocated_memory);
    
    
    print_results(allocator, output_file_name);

    return EXIT_SUCCESS;
}


void print_results(Allocator* allocator, const char* file_name) {
    FILE* results_file = NULL;
	Node* current = NULL;

	results_file = fopen(file_name, "w");

    fprintf(results_file, "-----freedMBList-----\n\n");
	current = allocator -> freedMBList -> head;
	while(current != NULL){
        fprintf(
            results_file,
            "Start address: %p | Size: %d \n", 
            current -> start_address,
            current -> size
        );	
		current = current -> next;
	}

    fprintf(results_file, "\n-----allocMBList-----\n\n");
    current = allocator -> allocMBList -> head;
	while(current != NULL){
        fprintf(
            results_file,
            "Start add: %p | Size: %d | Content: %s\n", 
            current -> start_address,
            current -> size,
            current -> content
        );	
		current = current->next;
	}

    fprintf(results_file, "\n---------------------------------------\n\n");

    fprintf(results_file, "Total nodes in freedMBList: %d\n", allocator -> freedMBList -> count);
    fprintf(results_file, "Total nodes in allocMBList: %d\n", allocator -> allocMBList -> count);
    fprintf(results_file, "Total memory allocated: %d\n", allocator -> total_allocated_memory);

	fclose(results_file);    
}

Boolean load_data(const char* data_file_name, int max_lines, Allocator* allocator) {
    FILE* data_file = NULL;
    char* line = NULL;
    char* token = NULL;
    int lines_read = 0;
    char input_name[NAME_LENGTH + EXTRA_SPACES];
    Boolean is_first_run = TRUE;

    if(data_file_name == NULL) {
        return FALSE;
    }
    
    if((data_file = fopen(data_file_name, "r")) == NULL) {
        fclose(data_file);
        return FALSE;
    }

    while(fgets(input_name, NAME_LENGTH + EXTRA_SPACES, data_file) != NULL) {
        token = strtok(input_name, "\n");
        lines_read++;   
        run_allocator_algorithm(allocator, token, is_first_run);
        if(lines_read >= max_lines) {
            lines_read = 0;            
            random_delete(allocator -> allocMBList, allocator -> freedMBList, NAMES_TO_DELETE);
            merge_consecutive_blocks(allocator -> freedMBList);
            is_first_run = FALSE;           
        }
    }

   free(line);
   fclose(data_file);
   
   return TRUE;

}

void run_allocator_algorithm(Allocator* allocator, const char* name, Boolean is_first_run) {
    if(allocator -> strategy == FIRST_FIT) {
        first_fit(name, allocator, is_first_run);
    }
    else if(allocator -> strategy == BEST_FIT) {
        best_fit(name, allocator, is_first_run);
    }
    else if(allocator -> strategy == WORST_FIT) {
        worst_fit(name, allocator, is_first_run);
    }
}

void* allocate_memory(Allocator* allocator, int size) {
    void* request;
    request = sbrk(size);
    allocator -> total_allocated_memory = allocator -> total_allocated_memory + size;
    return request;
}

Node* first_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    void* request; 
    Node* node = NULL;
    Node* pointer = NULL;
    Node* split = NULL;
    size_t name_size = strlen(name) + 1;
    Boolean found_block = FALSE;

    request = allocate_memory(allocator, name_size);
    strcpy((char*)request, name);

    /* Read the first 1000 names and add then to allocMBList */
    if(is_first_run) {
        node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
        add_to_list(allocator -> allocMBList, node, TRUE);
    }
    else {
        pointer = allocator -> freedMBList -> head;
        while(pointer != NULL) {
            split = NULL;
            /* Search in freedMBList for an available block of equal or greater size */
            if(pointer -> size >= name_size && pointer -> content == NULL) {
                /* Split the block if it is greater than the content size */           
                if(pointer -> size > name_size) {
                    split = split_block(pointer, name_size);
                }
                /* Add name to block content */
                pointer -> content = (char*)request;
                found_block = TRUE;
                /* Remove the node from freedMBList and add it to allocMBList */
                remove_node(allocator -> freedMBList, pointer);
                if(split != NULL) {
                    allocator -> freedMBList -> count = allocator -> freedMBList -> count + 1;
                }                
                pointer -> next = NULL;
                add_to_list(allocator -> allocMBList, pointer, TRUE);
                break;
            }
            pointer = pointer -> next;
        }
        if(found_block == FALSE) {       
            node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
            add_to_list(allocator -> allocMBList, node, TRUE);            
        }        
    }
    
    return pointer;
}

Node* best_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    void* request; 
    Node* node = NULL;
    Node* split = NULL;
    Node* best_fit = NULL;
    size_t name_size = strlen(name) + 1;
    Boolean found_block = FALSE;

    request = allocate_memory(allocator, name_size);
    strcpy((char*)request, name);

    /* Read the first 1000 names and add then to allocMBList */
    if(is_first_run) {
        node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
        add_to_list(allocator -> allocMBList, node, TRUE);
    }
    else {
        node = allocator -> freedMBList -> head;
        /* Loop through freedMBList, keeping track of the smallest node that will fit the size of the content */
        while(node != NULL) {
            if(node -> size >= name_size && node -> content == NULL) {
                if(best_fit != NULL && (node -> size - name_size < best_fit -> size - name_size)) {
                    best_fit = node;
                    found_block = TRUE;
                }
                else if(best_fit == NULL) {
                    best_fit = node;
                    found_block = TRUE;
                }
            }
            node = node -> next;
        }
        /* If an appropriate block is found in freedMBList, use it */
        if(found_block == TRUE) {
            if(best_fit -> size > name_size) {
                split = split_block(best_fit, name_size);
            }
            /* Add name to block content */
            best_fit -> content = (char*)request;
            /* Move node from freedMBList to allocMBList */
            remove_node(allocator -> freedMBList, best_fit);
            if(split != NULL) {
                allocator -> freedMBList -> count = allocator -> freedMBList -> count + 1;
            }            
            best_fit -> next = NULL;            
            add_to_list(allocator -> allocMBList, best_fit, TRUE);
        }
        /* If an appropriate block is not found in freedMBList, then create a new block and add it to allocMBList */
        else {         
            node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
            add_to_list(allocator -> allocMBList, node, TRUE);
            
        }
    }
    return node;
}

Node* worst_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    void* request; 
    Node* node = NULL;
    Node* split = NULL;
    Node* worst_fit = NULL;
    size_t name_size = strlen(name) + 1;
    Boolean found_block = FALSE;

    request = allocate_memory(allocator, name_size);
    strcpy((char*)request, name);

    /* Read the first 1000 names and add then to allocMBList */
    if(is_first_run) {
        node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
        add_to_list(allocator -> allocMBList, node, TRUE);
    }
    else {
        node = allocator -> freedMBList -> head;
        /* Loop through freedMBList, keeping track of the largest node that will fit the size of the content */
        while(node != NULL) {
            if(node -> size >= name_size && node -> content == NULL) {
                if(worst_fit != NULL && (node -> size - name_size > worst_fit -> size - name_size)) {
                    worst_fit = node;
                    found_block = TRUE;
                }
                else if(worst_fit == NULL) {
                    worst_fit = node;
                    found_block = TRUE;
                }
            }
            node = node -> next;
        }
        /* If an appropriate block is found in freedMBList, use it */
        if(found_block == TRUE) {
            if(worst_fit -> size > name_size) {
                split = split_block(worst_fit, name_size);
            }
            /* Add name to block content */
            worst_fit -> content = (char*)request;
            /* Move node from freedMBList to allocMBList */
            remove_node(allocator -> freedMBList, worst_fit);
            if(split != NULL) {
                allocator -> freedMBList -> count = allocator -> freedMBList -> count + 1;
            }            
            worst_fit -> next = NULL;            
            add_to_list(allocator -> allocMBList, worst_fit, TRUE);
        }
        /* If an appropriate block is not found in freedMBList, then create a new block and add it to allocMBList */
        else {          
            node = create_node(request, (char*)request + name_size - 1, name_size, (char*)request);
            add_to_list(allocator -> allocMBList, node, TRUE);            
        }
    }
    return node;
}

void merge_consecutive_blocks(List* list) {
    Node* pointer = NULL;
    Node* compare = NULL;
    int i = 0;
    int j = 0;

    pointer = list -> head;
    for(i = 0; i < list -> count; i++) {
        compare = list -> head;
        for(j = 0; j < list -> count; j++) {
            if(pointer -> start_address != compare -> start_address) {
                if(pointer -> end_address + 1 == compare -> start_address) {
                    pointer -> size = pointer -> size + compare -> size;
                    pointer -> end_address = compare -> end_address;                    
                    remove_node(list, compare);
                }
            }
            compare = compare -> next;
        }
        pointer = pointer -> next;
    }
}


void random_delete(List* allocMBList, List* freedMBList, int number) {
    int i;
    int j;
    int node_number;
    Node* node = NULL;
    
    for (i = 0; i < number; i++){
        if(allocMBList -> count == 0) {
            break;
        }
        else {
            node_number = rand() % allocMBList -> count;
        }
        node = allocMBList -> head;
         
        for(j = 0; j < node_number; j++) {
            node = node -> next;
        }
        node -> content = NULL;
        remove_node(allocMBList, node);
        node -> next = NULL;
        add_to_list(freedMBList, node, TRUE);
    }    
}

Allocator* create_allocator() {
    List* freedMBList;
    List* allocMBList;
    Allocator* allocator = (Allocator*)malloc(sizeof(Allocator));
    
    allocator -> freedMBList = freedMBList = create_list();
    allocator -> allocMBList = allocMBList = create_list();
    allocator -> total_allocated_memory = 0;

    return allocator;
}