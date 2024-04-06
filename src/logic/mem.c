#include "mem.h"

void calculate_memory_load_percentage(mem_t* memory)
{
    memory->memory_load.usage = memory->memory_load.total 
                                    - memory->memory_load.free 
                                    - memory->memory_load.buffers 
                                    - memory->memory_load.cached;
    memory->memory_percentage.usage = ((double)memory->memory_load.usage
                                        / (double)memory->memory_load.total * 100);
    memory->memory_percentage.free = (double)memory->memory_load.free 
                                        / (double)memory->memory_load.total * 100;
    memory->memory_percentage.cached = (double)memory->memory_load.cached 
                                        / (double)memory->memory_load.total * 100;
    memory->memory_percentage.buffers = (double)memory->memory_load.buffers 
                                        / (double)memory->memory_load.total * 100;

    memory->memory_load.swap_usage = memory->memory_load.swap_total 
                                        - memory->memory_load.swap_free;
    memory->memory_percentage.swap_usage = ((double)memory->memory_load.swap_usage 
                                            / (double)memory->memory_load.swap_total * 100);
    memory->memory_percentage.swap_free = (double)memory->memory_load.swap_free 
                                            / (double)memory->memory_load.swap_total * 100;
}

void init_memory(mem_t** memory)
{
    *memory = (mem_t*)calloc(1, sizeof(mem_t));
    
    scan_memory(*memory);
}

void free_memory(mem_t* memory)
{
    if (!memory)
        return;

    free(memory);
}