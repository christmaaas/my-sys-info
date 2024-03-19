#include "cpu.h"

#include <stdlib.h>

void get_cpu_info(cpu_t** cpu)
{
    if(*cpu)
        free_cpu(*cpu);

    *cpu = (cpu_t*)malloc(sizeof(cpu_t));
    
    cpu_init(*cpu);

    scan_cpu_basic_info(*cpu);
    scan_cpu_cache(*cpu);
    scan_cpu_clocks(*cpu);
}

void free_cpu(cpu_t* cpu)
{
    if(!cpu)
        return;
        
    for(size_t cpu_id = 0; cpu_id < cpu->processors_num; ++cpu_id)
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