#include "cpu.h"

#include <stdlib.h>

void init_cpu(cpu_t** cpu)
{
    *cpu = (cpu_t*)calloc(1, sizeof(cpu_t));
    
    init_cpu_cores(*cpu);

    scan_cpu_basic_info(*cpu);
    scan_cpu_cache(*cpu);
    scan_cpu_clocks(*cpu);
}

void calculate_total_cpu_load(cpu_t* cpu, const uint32_t graph_width)
{
    uint64_t user     = cpu->current_load.total.user; 
    uint64_t sys      = cpu->current_load.total.sys;
    uint64_t wait     = cpu->current_load.total.wait;
    uint64_t idle     = cpu->current_load.total.idle;
    uint64_t load_sum = 0;

    scan_cpu_load_stat(cpu); // refreshing data

    user     = cpu->current_load.total.user - user;
    sys      = cpu->current_load.total.sys - sys;   
    wait     = cpu->current_load.total.wait - wait;
    idle     = cpu->current_load.total.idle - idle;
    load_sum = user + sys + wait + idle;

    cpu->current_load.load_history[cpu->current_load.cur_point].user = ((double)user / (double)load_sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].sys  = ((double)sys / (double)load_sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].wait = ((double)wait / (double)load_sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].idle = ((double)idle / (double)load_sum) * 100.0;

    cpu->current_load.cur_point++;

    if (cpu->current_load.cur_point >= graph_width || cpu->current_load.cur_point >= MAX_CPU_LOAD_HISTORY_SIZE)
    {
        for (uint32_t i = 0; i < graph_width - 1 && i < MAX_CPU_LOAD_HISTORY_SIZE - 1; ++i)
            cpu->current_load.load_history[i] = cpu->current_load.load_history[i + 1];

        cpu->current_load.cur_point = graph_width - 1;
    }
}

void calculate_cpu_cores_load(cpu_t* cpu)
{
    loadtype_t* cur_cores = (loadtype_t*)calloc(cpu->processors_num, sizeof(loadtype_t));
    uint64_t    load_sum  = 0;

    for (uint32_t i = 0; i < cpu->processors_num; i++)
    {
        cur_cores[i].user = cpu->current_load.cores[i].user;
        cur_cores[i].sys  = cpu->current_load.cores[i].sys;
        cur_cores[i].wait = cpu->current_load.cores[i].wait;
        cur_cores[i].idle = cpu->current_load.cores[i].idle;
    }

    scan_cpu_load_stat(cpu);

    for (uint32_t i = 0; i < cpu->processors_num; i++)
    {
        cur_cores[i].user = cpu->current_load.cores[i].user - cur_cores[i].user;
        cur_cores[i].sys  = cpu->current_load.cores[i].sys - cur_cores[i].sys;
        cur_cores[i].wait = cpu->current_load.cores[i].wait - cur_cores[i].wait;
        cur_cores[i].idle = cpu->current_load.cores[i].idle - cur_cores[i].idle;
        load_sum          = cur_cores[i].user + cur_cores[i].sys 
                            + cur_cores[i].wait + cur_cores[i].idle;

        cpu->current_load.cores_load[i].user = ((double)cur_cores[i].user / (double)load_sum) * 100.0;
        cpu->current_load.cores_load[i].sys  = ((double)cur_cores[i].sys / (double)load_sum) * 100.0;
        cpu->current_load.cores_load[i].wait = ((double)cur_cores[i].wait / (double)load_sum) * 100.0;
        cpu->current_load.cores_load[i].idle = ((double)cur_cores[i].idle / (double)load_sum) * 100.0;
    }

    cpu->current_load.avg_load = 0; // resets at every iteration to calc avg load 
    for (uint32_t i = 0; i < cpu->processors_num; i++)
        cpu->current_load.avg_load += cpu->current_load.cores_load[i].user 
                                    + cpu->current_load.cores_load[i].sys 
                                    + cpu->current_load.cores_load[i].wait;

    cpu->current_load.avg_load /= cpu->processors_num;

    free(cur_cores);
}

void free_cpu(cpu_t* cpu)
{
    if (!cpu)
        return;
        
    for (uint32_t cpu_id = 0; cpu_id < cpu->processors_num; cpu_id++)
    {
        free(cpu->compound[cpu_id].frequency.freq_scaling_available_governors);
        free(cpu->compound[cpu_id].frequency.freq_scaling_governor);
        free(cpu->compound[cpu_id].frequency.freq_scaling_driver);
        free(cpu->compound[cpu_id].vendor_name);
        free(cpu->compound[cpu_id].model_name);
        free(cpu->compound[cpu_id].microcode_name);
        free(cpu->compound[cpu_id].flags);
        free(cpu->compound[cpu_id].bugs);
        free(cpu->compound[cpu_id].address_sizes);
        free(cpu->compound[cpu_id].energy_performance_preference);
        free(cpu->compound[cpu_id].ernergy_performance_available_preference);
    }   
    free(cpu->compound);
    free(cpu->current_load.cores);
    free(cpu->current_load.cores_load);
    free(cpu);
}