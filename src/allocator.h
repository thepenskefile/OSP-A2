#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "utility.h"
#include "linked_list.h"


#define FF "ff"
#define BF "bf"
#define WF "wf"

#define NUMBER_ARGUMENTS 4
#define NAMES_TO_READ 1000
#define NAMES_TO_DELETE 500

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} Strategy;


typedef struct allocator {
    List* allocMBList;
    List* freedMBList;
    Strategy strategy;
    int total_allocated_memory;
} Allocator;

void print_results(Allocator* allocator, const char* file_name);
Boolean load_data(const char* data_file_name, int max_lines, Allocator* allocator);
void run_allocator_algorithm(Allocator* allocator, char* name, Boolean is_first_run);
Node* first_fit(char* name, Allocator* allocator, Boolean is_first_run);
Node* best_fit(char* name, Allocator* allocator, Boolean is_first_run);
Node* worst_fit(char* name, Allocator* allocator, Boolean is_first_run);
void merge_consecutive_blocks(List* list);
void random_delete(List* allocMBList, List* freedMBList, int number);
Allocator* create_allocator();

#endif