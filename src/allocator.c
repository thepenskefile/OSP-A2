#include "allocator.h"

int main(int argc, char** argv) {
    const char* file_name;
    const char* allocator;
    List* allocMBList;
    List* freedMBList;

    if(argc != NUMBER_ARGUMENTS) {
        fprintf(stderr, "Error! Usage:\n\t%s <data file> <allocator>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    allocator = argv[2];

    allocMBList = create_list();
    freedMBList = create_list();

    
    printf("ALLOCATOR: %s\n", allocator);
    printf("DATA FILE NAME: %s\n", file_name);
    load_data(file_name, 4, allocator, allocMBList, freedMBList);
    
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
    

    return EXIT_SUCCESS;
}

Boolean load_data(const char* data_file_name, int max_lines, const char* allocator, List* allocMBList, List* freedMBList) {
    FILE* data_file = NULL;
    char* line = NULL;
    char* token = NULL;
    int lines_read = 0;
    char input_name[NAME_LENGTH + EXTRA_SPACES];

    if(data_file_name == NULL) {
        return FALSE;
    }
    
    if((data_file = fopen(data_file_name, "r")) == NULL) {
        fclose(data_file);
        return FALSE;
    }

    /*    
    while(getline(&line, &len, data_file) != -1) {
        strcpy(input_name, line);
        lines_read++;
        
        if(input_name[strlen(input_name) -1] == '\n') {
            input_name[strlen(input_name) - 1] = '\0';
        }
        
        printf("LINE: %s\n", input_name);
        run_allocator_algorithm(allocator, input_name);
        if(lines_read >= max_lines) {
            lines_read = 0;
            printf("DELETE\n");
        }
    }
    */

    while(fgets(input_name, NAME_LENGTH + EXTRA_SPACES, data_file) != NULL) {
        token = strtok(input_name, "\n");
        lines_read++;
        printf("LINE: %s\n", token);

        run_allocator_algorithm(allocator, token, allocMBList, freedMBList);
        if(lines_read >= max_lines) {
            lines_read = 0;
            printf("DELETE\n");
            random_delete(allocMBList, freedMBList, 2);
            printf("FINISH DELETE\n");
            merge_consecutive_blocks(freedMBList);
            printf("FINISH MERGE\n");
        }
    }

   free(line);
   fclose(data_file);
   
   return TRUE;

}

void run_allocator_algorithm(const char* allocator, const char* name, List* allocMBList, List* freedMBList) {
    if(strcmp(allocator, FIRST_FIT) == 0) {
        first_fit(name, allocMBList, freedMBList);
    }
    else if(strcmp(allocator, BEST_FIT) == 0) {
        best_fit(name, allocMBList, freedMBList);
    }
    else if(strcmp(allocator, WORST_FIT) == 0) {
        worst_fit(name, allocMBList, freedMBList);
    }
}

Node* first_fit(const char* name, List* allocMBList, List* freedMBList) {
    void* request; 
    Node* node = NULL;
    Node* pointer = NULL;
    size_t name_size = strlen(name) + 1;

    request = sbrk(name_size);
    strcpy((char*)request, name);

    if(freedMBList -> head == NULL) {
        node = create_node(request, (char*)request + 1, name_size, (char*)request);
        /*
        printf("START ADD: %p | SIZE: %d | CONTENT: %s\n", node -> start_address, node -> size, node -> content);
        */
        add_to_list(allocMBList, node, TRUE);        
    }
    else {
        pointer = freedMBList -> head;
        while(pointer != NULL) {
            if(pointer -> size >= name_size) {
                pointer -> content = (char*)request;
                break;
            }
            pointer = pointer -> next;
        }
    }
    return node;
}

void best_fit(const char* name, List* allocMBList, List* freedMBList) {
    printf("RUNNING BEST FIT\n");
}

void worst_fit(const char* name, List* allocMBList, List* freedMBList) {
    printf("RUNNING WORST FIT\n");
}

void merge_consecutive_blocks(List* list) {
    Node* pointer = NULL;
    Node* compare = NULL;

    pointer = list -> head;
    while(pointer != NULL) {
        compare = pointer -> next;
        while(compare != NULL) {
            
            if(pointer -> end_address == compare -> start_address) {
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

    printf("1\n");
    for (i = 0; i < number; i++){
        printf("WTF: %d\n", allocMBList -> count);
        if(allocMBList -> count == 0) {
            break;
        }
        if(allocMBList -> count == 1) {
            node_number = 1;
        }
        else {
            node_number = (rand() % (allocMBList -> count - 1));
        }        
        printf("WTF2\n");
        node = allocMBList -> head;
        printf("WTF3\n");
        printf("2: %d\n", node_number);
        if(node_number != 0) {
            printf("IF\n");
            for(j = 0; j < node_number - 1; j++) {
                printf("FOR: %d\n", j);
                previous = node;
                node = node -> next;
            }
        }
        printf("3\n");
        node -> content = NULL;
        if(previous == NULL) {
            allocMBList -> head = node -> next;
        }
        else {
            previous -> next = node -> next;
        }
        printf("4\n");
        node -> next = NULL;
        allocMBList -> count = allocMBList -> count - 1;
        printf("5\n");
        add_to_list(freedMBList, node, TRUE);
        printf("6\n");
    }    
}