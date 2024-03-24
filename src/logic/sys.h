#ifndef _SYS_H
#define _SYS_H

#include "cpu.h"


typedef struct system
{
    cpu_t* cpu;
    double time;


} system_t;

void init_system_data(system_t* data);

#endif /* _SYS_H */ 