#ifndef _CPU_UTILS_H
#define _CPU_UTILS_H

#include <stdint.h>

#define PATH_CPUINFO_FILE        "/proc/cpuinfo"
#define PATH_CPUS_PRESENT_FILE   "/sys/devices/system/cpu/present"
#define PATH_CPU_BYTE_ORDER_FILE "/sys/kernel/cpu_byteorder"
#define PATH_STAT_FILE           "/proc/stat"
#define PATH_CPUFREQ_FILE        "/sys/devices/system/cpu/cpufreq"

#define MAX_CPU_LOAD_HISTORY_SIZE 200

typedef enum cpu_byte_order_name
{
    LITTLE_ENDIAN_ORDER = 0,
    BIG_ENDIAN_ORDER    = 1
} cpubyteorder_t;

typedef struct cpu_frequency_info 
{
    uint32_t freq_max;
    uint32_t freq_base;
    uint32_t freq_cur;
    uint32_t freq_min;
    int      transition_latency;
    char*    freq_scaling_governor;
    uint32_t affected_cpus;
} cpufreq_t;

typedef struct cpu_cache_info 
{
    uint32_t levels_num;
    uint32_t l1_data_size;
    uint32_t l1_inst_size;
    uint32_t l2_size;
    uint32_t l3_size;
    uint32_t l4_size;
    uint32_t l1_data_line_size;
    uint32_t l1_inst_line_size;
    uint32_t l2_line_size;
    uint32_t l3_line_size;
    uint32_t l4_line_size;
    uint32_t l1_data_sets;
    uint32_t l1_inst_sets;
    uint32_t l2_sets;
    uint32_t l3_sets;
    uint32_t l4_sets;
    uint32_t l1_data_ways;
    uint32_t l1_inst_ways;
    uint32_t l2_ways;
    uint32_t l3_ways;
    uint32_t l4_ways;
} cpucache_t;

typedef struct cpu_topology
{
    uint16_t thread_id;
    uint16_t socket_id;
    uint16_t core_id;
} cputopology_t;

typedef struct cpu_compound_info
{
    char*          model_name;
    char*          vendor_name;
    uint16_t       cores_num;
    uint16_t       threads_num;
    uint32_t       model_number;
    uint32_t       family_number;
    uint32_t       stepping_number;
    uint32_t       cpuid_level;
    uint32_t       cache_alignment;
    char*          microcode_name;
    double         bogomips;
    cpubyteorder_t byte_oder;
    cpufreq_t      frequency;
    cpucache_t     cache;
    cputopology_t  topology;
} cpucompound_t;

typedef struct cpu_load_type
{
    uint64_t user;
    uint64_t nice;
    uint64_t sys;
    uint64_t idle;
    uint64_t wait;
} loadtype_t;

typedef struct cpu_load_percent
{
    double user;
    double sys;
    double idle;
    double wait;
} loadpercent_t;

typedef struct cpu_load
{
    loadtype_t     total;
    loadtype_t*    cores;
    loadpercent_t  load_history[MAX_CPU_LOAD_HISTORY_SIZE];
    loadpercent_t* cores_load;
    double         avg_load;
    uint32_t       cur_point;
} cpuload_t;

typedef struct cpu_info 
{
    uint32_t       processors_num; 
    cpucompound_t* compound;
    cpuload_t      current_load;
} cpu_t;

void init_cpu_cores(cpu_t* cpu_info);
void scan_cpu_basic_info(cpu_t* cpu);
void scan_cpu_clocks(cpu_t* cpu);
void refresh_cpu_clocks(cpu_t* cpu, const int proc_id);
void scan_cpu_load_stat(cpu_t* cpu);
void scan_cpu_cache(cpu_t* cpu);

#endif /* _CPU_UTILS_H */