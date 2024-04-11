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

void calculate_total_cpu_load(cpu_t* cpu, int graph_points_num)
{
    uint64_t user   = cpu->current_load.total.user; 
    uint64_t sys    = cpu->current_load.total.sys;
    uint64_t wait   = cpu->current_load.total.wait;
    uint64_t idle   = cpu->current_load.total.idle;
    uint64_t sum    = 0;

    scan_cpu_load_stat(cpu);

    user    = cpu->current_load.total.user - user;
    sys     = cpu->current_load.total.sys - sys;   
    wait    = cpu->current_load.total.wait - wait;
    idle    = cpu->current_load.total.idle - idle;
    sum     = user + sys + wait + idle;

    cpu->current_load.load_history[cpu->current_load.cur_point].user  = ((double)user / (double)sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].sys   = ((double)sys / (double)sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].wait  = ((double)wait / (double)sum) * 100.0;
    cpu->current_load.load_history[cpu->current_load.cur_point].idle  = ((double)idle / (double)sum) * 100.0;

    cpu->current_load.cur_point++;

    if (cpu->current_load.cur_point >= graph_points_num || cpu->current_load.cur_point >= MAX_CPU_LOAD_HISTORY_SIZE)
    {
        for (int i = 0; i < graph_points_num - 1 && i < MAX_CPU_LOAD_HISTORY_SIZE - 1; ++i)
            cpu->current_load.load_history[i] = cpu->current_load.load_history[i + 1];

        cpu->current_load.cur_point = graph_points_num - 1;
    }
}

loadpercent_t* calculate_cpu_cores_load(cpu_t* cpu)
{
    loadtype_t*     cores_load = (loadtype_t*)calloc(cpu->processors_num, sizeof(loadtype_t));
    loadpercent_t*  cores_load_percent = (loadpercent_t*)calloc(cpu->processors_num, sizeof(loadpercent_t));
    uint64_t        sum_of_loads = 0;

    for (uint32_t i = 0; i < cpu->processors_num; i++)
    {
        cores_load[i].user  = cpu->current_load.cores[i].user;
        cores_load[i].sys   = cpu->current_load.cores[i].sys;
        cores_load[i].wait  = cpu->current_load.cores[i].wait;
        cores_load[i].idle  = cpu->current_load.cores[i].idle;
    }

    scan_cpu_load_stat(cpu);

    for (uint32_t i = 0; i < cpu->processors_num; i++)
    {
        cores_load[i].user  = cpu->current_load.cores[i].user - cores_load[i].user;
        cores_load[i].sys   = cpu->current_load.cores[i].sys - cores_load[i].sys;
        cores_load[i].wait  = cpu->current_load.cores[i].wait - cores_load[i].wait;
        cores_load[i].idle  = cpu->current_load.cores[i].idle - cores_load[i].idle;
        sum_of_loads        = cores_load[i].user + cores_load[i].sys 
                                + cores_load[i].wait + cores_load[i].idle;

        cores_load_percent[i].user  = ((double)cores_load[i].user / (double)sum_of_loads) * 100.0;
        cores_load_percent[i].sys   = ((double)cores_load[i].sys / (double)sum_of_loads) * 100.0;
        cores_load_percent[i].wait  = ((double)cores_load[i].wait / (double)sum_of_loads) * 100.0;
        cores_load_percent[i].idle  = ((double)cores_load[i].idle / (double)sum_of_loads) * 100.0;
    }
    free(cores_load);

    return cores_load_percent;
}

double get_avg_cores_load(cpu_t* cpu, loadpercent_t* cores_load_percent)
{
    double avg_cores_load;
    for (uint32_t i = 0; i < cpu->processors_num; i++)
        avg_cores_load += cores_load_percent[i].user + cores_load_percent[i].sys + cores_load_percent[i].wait;

    return avg_cores_load / cpu->processors_num;
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
    free(cpu);
}