#ifndef _MEM_H
#define _MEM_H

#include "mem_utils.h"

void init_memory(mem_t** memory);
void free_memory(mem_t* memory);
void calculate_memory_usage_percentage(mem_t* memory);
void calculate_total_memory_load(mem_t* memory, int graph_points_num);

#endif /* _MEM_H */