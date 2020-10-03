#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>
#include <math.h>

#include "utility.h"
#include "linked_list.h"


#define FF "ff"
#define BF "bf"
#define WF "wf"

#define NUMBER_ARGUMENTS 3

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} Strategy;


typedef struct allocator {
    List* allocMBList;
    List* freedMBList;
    Strategy strategy;
} Allocator;


Boolean load_data(const char* data_file_name, int max_lines, Allocator* allocator);
void run_allocator_algorithm(Allocator* allocator, const char* name, Boolean is_first_run);
Node* first_fit(const char* name, Allocator* allocator, Boolean is_first_run);
void best_fit(const char* name, Allocator* allocator, Boolean is_first_run);
void worst_fit(const char* name, Allocator* allocator, Boolean is_first_run);
void merge_consecutive_blocks(List* list);
void random_delete(List* allocMBList, List* freedMBList, int number);
Allocator* create_allocator();

#endif