#ifndef _MEM_UI_H
#define _MEM_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_memory_page(WINDOW* main_page, mem_t* memory);
void print_memory_load_graph(WINDOW* main_page, mem_t* memory, int refresh_time, int graph_points_num);

#endif /* _MEM_UI_H */