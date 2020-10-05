#include "allocator.h"

int main(int argc, char** argv) {
    const char* file_name;
    const char* strategy;
    Allocator* allocator;

    if(argc != NUMBER_ARGUMENTS) {
        fprintf(stderr, "Error! Usage:\n\t%s <data file> <allocator>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    strategy = argv[2];

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
    
    printf("ALLOCATOR: %s\n", strategy);
    printf("DATA FILE NAME: %s\n", file_name);
    load_data(file_name, 4, allocator);
    
    /*
    while((offset = load_data(file_name, offset, 3, step_counter % 2, allocMBList, freedMBList)) != FALSE) {
        
        if(step_counter % 2 == ALLOCATE) {
           
            printf("ALLOCATE\n");
        }
        else {
            
            printf("DEALLOCATE\n");
        }
        printf("NEW BATCH: %ld\n", offset);
        step_counter++;
    }
    */

    printf("ALLOC MB\n");
    print_list(allocator -> allocMBList);
    printf("FREED MB\n");
    print_list(allocator -> freedMBList);
    printf("FREED MB COUNT: %d\n", allocator -> freedMBList -> count);

    return EXIT_SUCCESS;
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
        printf("LINE: %s\n", token);
        run_allocator_algorithm(allocator, token, is_first_run);
        /*
        printf("FREED MB\n");
        print_list(allocator -> freedMBList);
        printf("ALLOC MB\n");
        print_list(allocator -> allocMBList);  
        */
        if(lines_read >= max_lines) {
            lines_read = 0;
            printf("DELETE\n");
            random_delete(allocator -> allocMBList, allocator -> freedMBList, 2);
            
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

Node* first_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    void* request; 
    Node* node = NULL;
    Node* pointer = NULL;
    Node* previous = NULL;
    Node* split = NULL;
    size_t name_size = strlen(name) + 1;
    Boolean found_block = FALSE;

    request = sbrk(name_size);
    strcpy((char*)request, name);

    if(is_first_run) {
        node = create_node(request, (char*)request + name_size, name_size, (char*)request);
        add_to_list(allocator -> allocMBList, node, TRUE);
    }
    else {        
        pointer = allocator -> freedMBList -> head;
        while(pointer != NULL) {
            split = NULL;
            /* Search in freedMBList for an available block of equal or greater size */
            if(pointer -> size >= name_size && pointer -> content == NULL) {                
                if(pointer -> size > name_size) {
                    /*
                    split -> start_address = pointer -> start_address + name_size;
                    split -> end_address = pointer -> end_address;
                    split -> next = pointer -> next;
                    */
                    
                    pointer -> end_address = pointer -> start_address + name_size;
                    split = create_node(pointer -> end_address + 1, (pointer -> end_address + 1) + (pointer -> size - name_size), pointer -> size - name_size, NULL);                    
                    
                    split -> content = (char*)pointer -> end_address + 1;                    
                             
                    split -> start_address = pointer -> end_address + 1;                    
                    split -> end_address = split -> start_address + (pointer -> size - name_size);                    
                    split -> size = pointer -> size - name_size;                    
                    pointer -> size = name_size;
                    
                    split -> next = pointer -> next;
                    pointer -> next = split;
                    
                    
                }
                /* Add name to block content */
                pointer -> content = (char*)request;
                found_block = TRUE;
                /* Move node from freedMBList to allocMBList */
                if(previous == NULL) {
                    allocator -> freedMBList -> head = pointer -> next;
                }
                else {
                    previous -> next = pointer -> next;
                }
                pointer -> next = NULL;
                add_to_list(allocator -> allocMBList, pointer, TRUE);
                break;
            }
            previous = pointer;
            pointer = pointer -> next;
        }
        if(found_block == FALSE) {
            /*
            printf("FREED MB2\n");
            print_list(freedMBList);
            */
            
            node = create_node(request, (char*)request + 1, name_size, (char*)request);
            /*
            printf("FREED MB3\n");
            print_list(freedMBList);
            */
            add_to_list(allocator -> allocMBList, node, TRUE);
            
            
        }        
    }
    
    return node;
}

void best_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    printf("RUNNING BEST FIT\n");
}

void worst_fit(const char* name, Allocator* allocator, Boolean is_first_run) {
    printf("RUNNING WORST FIT\n");
}

void merge_consecutive_blocks(List* list) {
    Node* pointer = NULL;
    Node* compare = NULL;

    pointer = list -> head;
    while(pointer != NULL) {
        compare = pointer -> next;
        while(compare != NULL) {           
            if(compare -> content == NULL && pointer -> content == NULL) {
                if(pointer -> end_address == compare -> start_address) {
                    printf("MERGING\n");
                    pointer -> size = pointer -> size + compare -> size;
                    pointer -> end_address = compare -> end_address;
                    pointer -> next = compare -> next;
                    free(compare);
                    compare = pointer -> next;
                }
                else {
                    compare = compare -> next;  
                }  
            }
            else {
                compare = compare -> next;  
            }                    
        }

        pointer = pointer -> next;

        /*
        if(previous -> content == NULL && pointer -> content == NULL) {
            previous -> size = previous -> size + pointer -> size;
            previous -> next = pointer -> next;
            free(pointer);
            pointer = previous;
            previous = NULL;
        } else {
            previous = pointer;
            pointer = pointer -> next;
        }
        */

    }
}

void random_delete(List* allocMBList, List* freedMBList, int number) {
    int i;
    int j;
    int node_number;
    Node* node = NULL;
    Node* previous = NULL;
    
    for (i = 0; i < number; i++){
        previous = NULL;
        if(allocMBList -> count == 0) {
            break;
        }
        else {
            node_number = rand() % allocMBList -> count;
        }
        node = allocMBList -> head;
         
        for(j = 0; j < node_number; j++) {
            previous = node;
            node = node -> next;
        }
        printf("DELETING: %s\n", node -> content);
        node -> content = NULL;
        if(previous == NULL) {
            allocMBList -> head = node -> next;
        }
        else {
            previous -> next = node -> next;
        }
        node -> next = NULL;
        allocMBList -> count = allocMBList -> count - 1;
        /*
        add_to_list(freedMBList, node, TRUE);
        printf("FREED MB\n");
        print_list(freedMBList);
        printf("ALLOC MB\n");
        print_list(allocMBList);  
        */
    }    
}

Allocator* create_allocator() {
    List* freedMBList;
    List* allocMBList;
    Allocator* allocator = (Allocator*)malloc(sizeof(Allocator));
    
    allocator -> freedMBList = freedMBList = create_list();
    allocator -> allocMBList = allocMBList = create_list();

    return allocator;
}