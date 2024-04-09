#ifndef _MEM_UI_H
#define _MEM_UI_H

#include "macro_ui.h"
#include "../logic/sys.h"

void print_memory_page(WINDOW* main_page, system_t* data);
void print_memory_load_graph(WINDOW* main_page, system_t* data, int refresh_time);

#endif /* _MEM_UI_H */