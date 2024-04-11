#ifndef _CPU_UI_H
#define _CPU_UI_H

#include "common_ui.h"
#include "../logic/sys.h"

void print_cpu_info_page(WINDOW* main_page, cpu_t* cpu, int selected_processor_id);
void print_cpu_load_graph(WINDOW* main_page, cpu_t* cpu, int refresh_time);
void print_cpu_cores_load(WINDOW* main_page, cpu_t* cpu, int refresh_time, int current_cols);

#endif /* _CPU_UI_H */