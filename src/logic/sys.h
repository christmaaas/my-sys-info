#ifndef _SYS_H
#define _SYS_H

#include "cpu.h"
#include "mem.h"


typedef struct system
{
    cpu_t* cpu;
    mem_t* memory;

} system_t;

void init_system_data(system_t** data);
void free_system_data(system_t* data);

#endif /* _SYS_H */ 