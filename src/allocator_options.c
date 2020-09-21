#include "allocator_options.h"

long load_data(const char* data_file_name, long offset, int max_lines) {
    FILE* data_file = NULL;
    char* line = NULL;
    size_t len = 0;
    char* token = NULL;
    long new_offset = 0;
    int lines_read = 0;

    
    char input_name[NAME_LENGTH + EXTRA_SPACES];

    
    if(data_file_name == NULL || offset < 0) {
        return FALSE;
    }

    
    if((data_file = fopen(data_file_name, "r")) == NULL) {
        fclose(data_file);
        return FALSE;
    }

        
    if(offset > 0 && fseek(data_file, offset, SEEK_SET) != 0) {
        fclose(data_file);
        return FALSE;
    }


    while(getline(&line, &len, data_file) != -1) {
        strcpy(input_name, line);
        lines_read++;
        
        if(input_name[strlen(input_name) -1] == '\n') {
            input_name[strlen(input_name) - 1] = '\0';
        }
        
        printf("LINE: %s\n", input_name);   
        new_offset = ftell(data_file);   
        if(lines_read >= max_lines) {
            free(line);
            fclose(data_file);
            return new_offset;
        }   
    }

    printf("NEW OFFSET: %ld\n", new_offset);

   free(line);
   fclose(data_file);
   
   return FALSE;
}

