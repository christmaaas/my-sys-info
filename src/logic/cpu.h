#ifndef _CPU_H
#define _CPU_H

#include "../facilities/cpu_facility.h"

void get_cpu_info(cpu_t** cpu);
void free_cpu(cpu_t* cpu);

#endif /* _CPU_H */