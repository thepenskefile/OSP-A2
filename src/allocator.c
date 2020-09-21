#include "allocator.h"

int main(int argc, char** argv) {
    const char* file_name;
    const char* algorithm;
    int offset = 0;

    file_name = argv[1];

    printf("WTF");
    printf("DATA FILE NAME: %s", file_name);

    
    while((offset = load_data(file_name, offset, 3)) != FALSE) {
        printf("NEW BATCH: %ld\n", offset);
    }
    

    return EXIT_SUCCESS;
}