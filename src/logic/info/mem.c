#include "mem.h"

#include <stdlib.h>

void calculate_memory_usage_percentage(mem_t* memory)
{
    scan_memory(memory);

    memory->memory_usage.usage = memory->memory_usage.total 
                                    - memory->memory_usage.free 
                                    - memory->memory_usage.buffers 
                                    - memory->memory_usage.cached;
    memory->memory_percentage.usage = ((double)memory->memory_usage.usage
                                        / (double)memory->memory_usage.total * 100);
    memory->memory_percentage.free = (double)memory->memory_usage.free 
                                        / (double)memory->memory_usage.total * 100;
    memory->memory_percentage.cached = (double)memory->memory_usage.cached 
                                        / (double)memory->memory_usage.total * 100;
    memory->memory_percentage.buffers = (double)memory->memory_usage.buffers 
                                        / (double)memory->memory_usage.total * 100;

    memory->memory_usage.swap_usage = memory->memory_usage.swap_total 
                                        - memory->memory_usage.swap_free;
    memory->memory_percentage.swap_usage = ((double)memory->memory_usage.swap_usage 
                                            / (double)memory->memory_usage.swap_total * 100);
    memory->memory_percentage.swap_free = (double)memory->memory_usage.swap_free 
                                            / (double)memory->memory_usage.swap_total * 100;
}

void calculate_total_memory_load(mem_t* memory, int graph_points_num)
{
    calculate_memory_usage_percentage(memory);

    memory->current_load.ram_load_history[memory->current_load.cur_point] = memory->memory_percentage.usage;
    memory->current_load.swap_load_history[memory->current_load.cur_point] = memory->memory_percentage.swap_usage;

    memory->current_load.cur_point++;

    if (memory->current_load.cur_point >= graph_points_num || memory->current_load.cur_point >= MAX_MEM_LOAD_HISTORY_SIZE)
    {
        for (int i = 0; i < graph_points_num - 1 && i < MAX_MEM_LOAD_HISTORY_SIZE - 1; ++i)
        {
            memory->current_load.ram_load_history[i] = memory->current_load.ram_load_history[i + 1];
            memory->current_load.swap_load_history[i] = memory->current_load.swap_load_history[i + 1];
        }
        memory->current_load.cur_point = graph_points_num - 1;
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