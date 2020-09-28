#include "allocator.h"

int main(int argc, char** argv) {
    const char* file_name;
    const char* allocator;
    int offset = 0;
    int step_counter = 0;
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
    load_data(file_name, 3, allocator, allocMBList, freedMBList);
    
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
    size_t wsize;

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

        run_allocator_algorithm(allocator, token);
        if(lines_read >= max_lines) {
            lines_read = 0;
            printf("DELETE\n");
        }
    }

   free(line);
   fclose(data_file);
   
   return TRUE;

}

void run_allocator_algorithm(const char* allocator, const char* name) {
    if(strcmp(allocator, FIRST_FIT) == 0) {
        first_fit(name);
    }
    else if(strcmp(allocator, BEST_FIT) == 0) {
        best_fit(name);
    }
    else if(strcmp(allocator, WORST_FIT) == 0) {
        worst_fit(name);
    }
}

void first_fit(const char* name) {
    void* request; 
    size_t name_size = strlen(name) + 1;
    printf("SIZE: %d\n", name_size);
    printf("RUNNING FIRST FIT\n");
    
    request = sbrk(name_size);
    printf("REQUEST 1: %p\n", request);
    strcpy((char *)request, name);
    printf("REQUEST 2: %s\n", (char*)request);
    /*node = create_node();*/
}

void best_fit(const char* name) {
    printf("RUNNING BEST FIT\n");
}

void worst_fit(const char* name) {
    printf("RUNNING WORST FIT\n");
}