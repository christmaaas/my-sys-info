#ifndef _MEM_H
#define _MEM_H

#include "mem_utils.h"

void init_memory(mem_t** memory);
void free_memory(mem_t* memory);
void calculate_memory_load_percentage(mem_t* memory);

#endif /* _MEM_H */