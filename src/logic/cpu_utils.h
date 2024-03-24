#ifndef _CPU_UTILS_H
#define _CPU_UTILS_H

#include "../utils/utils.h"

#include <stdint.h>

#define PATH_CPUINFO_FILE          "/proc/cpuinfo"
#define PATH_CPUS_PRESENT_FILE     "/sys/devices/system/cpu/present"
#define PATH_CPU_BYTE_ORDER_FILE   "/sys/kernel/cpu_byteorder"

/* можно сделать так. делаю просто общую структуру cpu, в ней общие данные.
в ядрах изменяется только кэш, частота, индексы и впр все.
значит можно сделать в cpu указатель на структуры freq, cache, topology.
потом уже в моих функциях, просто парсить количество ядер и выделять память на массив из ядер,
а точнее на freq, cache, topology которых будет столько сколько ядер(потоков) в проце.

 */

typedef enum cpu_byte_order_name
{
    LITTLE_ENDIAN_ORDER = 0,
    BIG_ENDIAN_ORDER = 1
} cpubyteorder_t; // насчет _t у enum не уверен

typedef struct cpu_frequency_info 
{
    //uint32_t thread_id; в общей структуре для ядер будет id

    uint32_t        freq_max;
    uint32_t        freq_base;
    uint32_t        freq_cur;
    uint32_t        freq_min;

    int             transition_latency;

    char*           freq_scaling_driver;
    char*           freq_scaling_governor;
    char*           freq_scaling_available_governors;

    uint32_t        affected_cpus; // shared_list у них
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
    uint32_t        thread_id;  // у меня последний 16
    uint32_t        socket_id;  // как я понял это physical_id из /proc/cpuinfo
    uint32_t        core_id;    // у меня последний 24

    //...

} cputopology_t;

typedef struct cpu_compound_info
{
    char*           model_name;
    char*           vendor_name;

    uint32_t        cores_num;
    uint32_t        threads_num;
    uint32_t        phys_cpus_num;  

    uint32_t        model_number;  // у них все три эти значения инты, но им вроде соответсвует название, а инт этот как их код, поэтому можно сделать char* 
    uint32_t        family_number;
    uint32_t        stepping_number; // хз что это, наверное выкинуть

    uint32_t        cpuid_level;
    uint32_t        clflush_size;
    uint32_t        cache_alignment;  
    char*           microcode_name; // у них char* и в нем строка типа 0x430, но можно сделать числом
    double          bogomips;
    cpubyteorder_t  byte_oder;

    cpufreq_t       frequency;

    cpucache_t      cache;      // по сути должно быть массив на 4 элемента, но мб кэш будет разный на разных процах
    
    cputopology_t   topology; // мб не cores а threads и еще по замыслу это будет указатель на массив с этими ядрами/потоками которых у меня 16 

    char*           flags;

    char*           bugs;

    char*           energy_performance_preference;
    char*           ernergy_performance_available_preference; 

    char*           address_sizes;
} cpucompound_t;

typedef struct cpu_info 
{
    uint32_t        processors_num; // мб название поменять, да и в целом названия во всех страктах посмотреть
    cpucompound_t*  compound;
} cpu_t;


// может что из того что ниже пригодится 

    //char *flags;
    //char *bugs;
    //char *pm;             /* power management features */
    //int cache_size;
    //float bogomips;
    //char *microcode;

    //int id;
    //cpu_topology_data *cputopo;
    //cpufreq_data *cpufreq;

    //char *has_fpu;
    //char *bug_fdiv, *bug_hlt, *bug_f00f, *bug_coma;

    //nt model, family, stepping;
    //char *strmodel;

    //GSList *cache;


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
void scan_cpu_topology(cpu_t* cpu);

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