#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>

#include "facilities.h"

/* можно сделать так. делаю просто общую структуру cpu, в ней общие данные.
в ядрах изменяется только кэш, частота, индексы и впр все.
значит можно сделать в cpu указатель на структуры freq, cache, topology.
потом уже в моих функциях, просто парсить количество ядер и выделять память на массив из ядер,
а точнее на freq, cache, topology которых будет столько сколько ядер(потоков) в проце.

 */

typedef enum cpu_byte_order
{
    _LITTLE_ENDIAN_ORDER = 0,
    _BIG_ENDIAN_ORDER = 1
} byte_order;

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

    char*           affected_cpus; // shared_list у них
} cpufreq_t;

typedef struct cpu_cache_info
{
    uint32_t        level;
    uint32_t        number_of_sets;
    uint32_t        physical_line_partition;
    uint32_t        size;
    char*           type;
    uint32_t        ways_of_associativity;
    uint32_t        uid; /* uid is unique among caches with the same (type, level) */
    char*           shared_cpu_list; /* some kernel's don't give a uid, so try shared_cpu_list */
    uint32_t        phy_sock;

    char*           allocation_policy;
	char*           write_policy;

} cpucache_t;

typedef struct cpu_topology_info
{
    uint32_t        thread_id;  // у меня последний 16
    uint32_t        socket_id;  // как я понял это physical_id из /proc/cpuinfo
    uint32_t        core_id;    // у меня последний 24

    cpufreq_t*      frequency;
    cpucache_t*     cache;

    //...

} cputopology_t;

typedef struct cpu 
{
    char*           model_name;
    char*           vendor_name;

    uint32_t        cores_count;
    uint32_t        threads_count;
    uint32_t        phys_cpus_count;

    uint32_t        model_number;  // у них все три эти значения инты, но им вроде соответсвует название, а инт этот как их код, поэтому можно сделать char* 
    uint32_t        family_number;
    uint32_t        stepping_number; // хз что это, наверное выкинуть

    char*           architecture_name;
    uint32_t        cache_size;
    char*           microcode_name; // у них char* и в нем строка типа 0x430, но можно сделать числом
    double          bogomips;
    byte_order      byte_oder;

    cputopology_t*  cores; // мб не cores а threads и еще по замыслу это будет указатель на массив с этими ядрами/потоками которых у меня 16 

    char*           flags;

    char*           fpu;

    char*           bugs;

    char*           energy_performance_pref;
    char*           ernergy_performance_available_pref; 

    char*           adress;

    char*           power_management;



    // может что из того что ниже пригодится 

    char *flags;
    char *bugs;
    char *pm;             /* power management features */
    int cache_size;
    float bogomips;
    char *microcode;

    int id;
    //cpu_topology_data *cputopo;
    //cpufreq_data *cpufreq;

    char *has_fpu;
    char *bug_fdiv, *bug_hlt, *bug_f00f, *bug_coma;

    int model, family, stepping;
    char *strmodel;

    //GSList *cache;



} cpu_t;



#endif /* _CPU_H */