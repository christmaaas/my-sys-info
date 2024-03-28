#ifndef _CPU_UTILS_H
#define _CPU_UTILS_H

#include "../utils/utils.h"

#include <stdint.h>

#define PATH_CPUINFO_FILE          "/proc/cpuinfo"
#define PATH_CPUS_PRESENT_FILE     "/sys/devices/system/cpu/present"
#define PATH_CPU_BYTE_ORDER_FILE   "/sys/kernel/cpu_byteorder"
#define PATH_STAT_FILE             "/proc/stat"

#define MAX_LOAD_HISTORY_SIZE       200

typedef enum cpu_byte_order_name
{
    LITTLE_ENDIAN_ORDER = 0,
    BIG_ENDIAN_ORDER = 1
} cpubyteorder_t;

typedef struct cpu_frequency_info 
{
    uint32_t        freq_max;
    uint32_t        freq_base;
    uint32_t        freq_cur;
    uint32_t        freq_min;

    int             transition_latency;

    char*           freq_scaling_driver;
    char*           freq_scaling_governor;
    char*           freq_scaling_available_governors;

    uint32_t        affected_cpus;
} cpufreq_t;

typedef struct cpu_cache_info 
{
    uint32_t        levels_num;

    uint32_t        l1_data_size;
    uint32_t        l1_inst_size;
    uint32_t        l2_size;
    uint32_t        l3_size;
    uint32_t        l4_size;

    uint32_t        l1_data_line_size;
    uint32_t        l1_inst_line_size;
    uint32_t        l2_line_size;
    uint32_t        l3_line_size;
    uint32_t        l4_line_size;

    uint32_t        l1_data_sets;
    uint32_t        l1_inst_sets;
    uint32_t        l2_sets;
    uint32_t        l3_sets;
    uint32_t        l4_sets;

    uint32_t        l1_data_ways;
    uint32_t        l1_inst_ways;
    uint32_t        l2_ways;
    uint32_t        l3_ways;
    uint32_t        l4_ways;
} cpucache_t;

typedef struct cpu_topology_info
{
    uint32_t        thread_id; 
    uint32_t        socket_id;  
    uint32_t        core_id;    
} cputopology_t;

typedef struct cpu_compound_info
{
    char*           model_name;
    char*           vendor_name;

    uint32_t        cores_num;
    uint32_t        threads_num;
    uint32_t        phys_cpus_num;  

    uint32_t        model_number; 
    uint32_t        family_number;
    uint32_t        stepping_number;

    uint32_t        cpuid_level;
    uint32_t        clflush_size;
    uint32_t        cache_alignment;  
    char*           microcode_name; 
    double          bogomips;
    cpubyteorder_t  byte_oder;

    cpufreq_t       frequency;

    cpucache_t      cache;     
    
    cputopology_t   topology; 

    char*           flags;

    char*           bugs;

    char*           energy_performance_preference;
    char*           ernergy_performance_available_preference; 

    char*           address_sizes;
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
    loadtype_t  total;
    loadtype_t* cores;
} cpuload_t;

typedef struct cpu_info 
{
    uint32_t        processors_num; 
    cpucompound_t*  compound;

    cpuload_t*      current_load;
    uint32_t        cur_point;
    loadpercent_t   load_history[MAX_LOAD_HISTORY_SIZE];
} cpu_t;

void init_cpu_cores(cpu_t* cpu_info);

typedef enum cpu_info_tokens
{
    PROCESSOR_NUM       = 0,
    VENDOR_ID           = 1,
    CPU_FAMILY          = 2,
    MODEL               = 3,
    MODEL_NAME          = 4,
    STEPPING            = 5,
    MICROCODE           = 6,
    FREQUENCY_MHZ       = 7,
    CACHE_SIZE          = 8,
    PHYSICAL_ID         = 9,
    SIBLINGS            = 10,
    CORE_ID             = 11,
    CPU_CORES           = 12,
    APICID              = 13,
    INITIAL_APICID      = 14,
    FPU                 = 15,
    FPU_EXCEPTION       = 16,
    CPUID_LEVEL         = 17,
    WP                  = 18,
    FLAGS               = 19,
    VMX_FLAGS           = 20,
    BUGS                = 21,
    BOGOMIPS            = 22,
    CLFLUSH_SIZE        = 23,
    CACHE_ALIGNMENT     = 24,
    ADDRESS_SIZES       = 25,
    POWER_MANAGMENT     = 26
} cpu_info_tokens_t;

void scan_cpu_basic_info(cpu_t* cpu);
void scan_cpu_clocks(cpu_t* cpu);
void refresh_cpu_clocks(cpu_t* cpu, int processor_id);
void scan_cpu_load_stat(cpu_t* cpu);

typedef enum cpu_cache_levels
{
    L1_DATA_LEVEL           = 0,
    L1_INSTRUCTION_LEVEL    = 1,
    L2_LEVEL                = 2,
    L3_LEVEL                = 3,
    L4_LEVEL                = 4
} cache_level_t;

void scan_cpu_cache(cpu_t* cpu);

#endif /* _CPU_UTILS_H */