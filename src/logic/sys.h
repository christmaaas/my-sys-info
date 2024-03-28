#ifndef _SYS_H
#define _SYS_H

#include "cpu.h"


typedef struct system
{
    cpu_t* cpu;


} system_t;

void init_system_data(system_t** data);
void free_system_data(system_t* data);

#endif /* _SYS_H */ 