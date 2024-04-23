#ifndef _SYS_H
#define _SYS_H

#include "cpu.h"
#include "mem.h"
#include "net.h"
#include "pci.h"
#include "sensors.h"

typedef struct system_info
{
    cpu_t*    cpu;
    mem_t*    memory;
    net_t*    network;
    pci_t*    pci;
    sensor_t* sensor;   
} system_t;

void init_system_data(system_t** data);
void free_system_data(system_t* data);

#endif /* _SYS_H */ 