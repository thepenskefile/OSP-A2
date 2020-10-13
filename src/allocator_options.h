#ifndef SCHEDULER_OPTIONS_H
#define SCHEDULER_OPTIONS_H

#include "utility.h"
#include "linked_list.h"

long load_data_old(const char* data_file_name, long offset, int max_lines, Step step, List* allocMBList, List* freedMBList);

#endif