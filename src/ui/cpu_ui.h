#ifndef _CPU_UI_H
#define _CPU_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_cpu_info_page(WINDOW* main_page, cpu_t* cpu, const int proc_id);
void print_cpu_load_graph(WINDOW* main_page, 
                        cpu_t* cpu, 
                        const int time, 
                        const int graph_width);
void print_cpu_cores_load(WINDOW* main_page, 
                        cpu_t* cpu, 
                        const int time, 
                        const int cols);

#endif /* _CPU_UI_H */