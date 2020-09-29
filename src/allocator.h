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

#define FIRST_FIT "ff"
#define BEST_FIT "bf"
#define WORST_FIT "wf"
#define NUMBER_ARGUMENTS 3

Boolean load_data(const char* data_file_name, int max_lines, const char* allocator, List* allocMBList, List* freedMBList);
void run_allocator_algorithm(const char* allocator, const char* name, List* allocMBList, List* freedMBList);
Node* first_fit(const char* name, List* allocMBList, List* freedMBList);
void best_fit(const char* name, List* allocMBList, List* freedMBList);
void worst_fit(const char* name, List* allocMBList, List* freedMBList);
void merge_consecutive_blocks(List* list);
void random_delete(List* allocMBList, List* freedMBList, int number);


#endif