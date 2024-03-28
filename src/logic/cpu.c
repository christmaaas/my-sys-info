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

void calculate_current_load(cpu_t* cpu, int points_num)
{
    uint64_t user   = cpu->current_load->total.user; 
    uint64_t sys    = cpu->current_load->total.sys;
    uint64_t wait   = cpu->current_load->total.wait;
    uint64_t idle   = cpu->current_load->total.idle;
    uint64_t sum    = 0;

    scan_cpu_load_stat(cpu);

    user    = cpu->current_load->total.user - user;
    sys     = cpu->current_load->total.sys - sys;   
    wait    = cpu->current_load->total.wait - wait;
    idle    = cpu->current_load->total.idle - idle;
    sum     = user + sys + wait + idle;

    cpu->load_history[cpu->cur_point].user  = ((double)user / (double)sum) * 100.0;
    cpu->load_history[cpu->cur_point].sys   = ((double)sys / (double)sum) * 100.0;
    cpu->load_history[cpu->cur_point].wait  = ((double)wait / (double)sum) * 100.0;
    cpu->load_history[cpu->cur_point].idle  = ((double)idle / (double)sum) * 100.0;

    cpu->cur_point++;

    if (cpu->cur_point >= points_num || cpu->cur_point >= MAX_LOAD_HISTORY_SIZE)
    {
        for (int i = 0; i < points_num - 1 && i < MAX_LOAD_HISTORY_SIZE - 1; ++i)
            cpu->load_history[i] = cpu->load_history[i + 1];

        cpu->cur_point = points_num - 1;
    }
}

void free_cpu(cpu_t* cpu)
{
    if (!cpu)
        return;
        
    for (size_t cpu_id = 0; cpu_id < cpu->processors_num; ++cpu_id)
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
    free(cpu);
}