#include "mem.h"

#include <stdlib.h>

void calculate_memory_usage_percentage(mem_t* memory)
{
    scan_memory(memory); // refreshing data

    memory->usage_stats.usage = memory->usage_stats.total 
                                    - memory->usage_stats.free 
                                    - memory->usage_stats.buffers 
                                    - memory->usage_stats.cached;
    memory->usage_percentage.usage = ((double)memory->usage_stats.usage
                                        / (double)memory->usage_stats.total * 100);
    memory->usage_percentage.free = (double)memory->usage_stats.free 
                                        / (double)memory->usage_stats.total * 100;
    memory->usage_percentage.cached = (double)memory->usage_stats.cached 
                                        / (double)memory->usage_stats.total * 100;
    memory->usage_percentage.buffers = (double)memory->usage_stats.buffers 
                                        / (double)memory->usage_stats.total * 100;

    memory->usage_stats.swap_usage = memory->usage_stats.swap_total 
                                        - memory->usage_stats.swap_free;
    memory->usage_percentage.swap_usage = ((double)memory->usage_stats.swap_usage 
                                            / (double)memory->usage_stats.swap_total * 100);
    memory->usage_percentage.swap_free = (double)memory->usage_stats.swap_free 
                                            / (double)memory->usage_stats.swap_total * 100;
}

void calculate_total_memory_load(mem_t* memory, const uint32_t graph_width)
{
    calculate_memory_usage_percentage(memory);

    memory->current_load.ram_load_history[memory->current_load.cur_point] = memory->usage_percentage.usage;
    memory->current_load.swap_load_history[memory->current_load.cur_point] = memory->usage_percentage.swap_usage;

    memory->current_load.cur_point++;

    if (memory->current_load.cur_point >= graph_width || memory->current_load.cur_point >= MAX_MEM_LOAD_HISTORY_SIZE)
    {
        for (uint32_t i = 0; i < graph_width - 1 && i < MAX_MEM_LOAD_HISTORY_SIZE - 1; ++i)
        {
            memory->current_load.ram_load_history[i] = memory->current_load.ram_load_history[i + 1];
            memory->current_load.swap_load_history[i] = memory->current_load.swap_load_history[i + 1];
        }
        memory->current_load.cur_point = graph_width - 1;
    }
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