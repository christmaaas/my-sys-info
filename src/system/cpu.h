#ifndef _CPU_H
#define _CPU_H

#include "facilities.h"

typedef struct frequency_info {
    uint32_t id;

    uint32_t freq_max;
    uint32_t freq_base;
    uint32_t freq_cur;
    uint32_t freq_min;

    int transition_latency;

    char* freq_scaling_driver;
    char* freq_scaling_governor;
    char* freq_scaling_available_governors;

    char* affected_cpus; // shared_list у них
} frequency_t;

typedef struct configuration_info {
    uint32_t id; /* thread */

    uint32_t socket_id; // как я понял это physical_id из /proc/cpuinfo
    uint32_t core_id;

    uint32_t book_id; // не точно
    uint32_t drawer_id; // не точно
} configuration_t; // topology

typedef struct cpu {
    char* model_name;
    char* vendor_name;

    uint32_t model;  // у них все три эти значения инты, но им вроде соответсвует название, а инт этот как их код, поэтому можно сделать char* 
    uint32_t family;
    uint32_t stepping; // хз что это, наверное выкинуть

    char* architecture;
    uint32_t cache_size;
    char* microcode; // у них char* и в нем строка типа 0x430, но можно сделать числом
    double bogomips;

    char* flags;

    char* fpu;

    char* bugs;

    char* energy_performance_pref;
    char* ernergy_performance_available_pref;

    byte_order byte_oder;

    frequency_t* frequency;
    configuration_t* configuration; 

    char* adress;

    char* power_management;





    char *flags;
    char *bugs;
    char *pm;             /* power management features */
    int cache_size;
    float bogomips;
    char *microcode;

    int id;
    float cpu_mhz; /* for devices.c, identical to cpukhz_max/1000 */
    //cpu_topology_data *cputopo;
    //cpufreq_data *cpufreq;

    char *has_fpu;
    char *bug_fdiv, *bug_hlt, *bug_f00f, *bug_coma;

    int model, family, stepping;
    char *strmodel;

    //GSList *cache;



} cpu_t;



#endif /* _CPU_H */