#ifndef _CPU_H
#define _CPU_H

#include "cpu_utils.h"

void init_cpu(cpu_t** cpu);
void free_cpu(cpu_t* cpu);
void calculate_total_cpu_load(cpu_t* cpu, int graph_points_num);
void calculate_cpu_cores_load(cpu_t* cpu);

#endif /* _CPU_H */