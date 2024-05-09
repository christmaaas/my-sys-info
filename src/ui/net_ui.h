#ifndef _NET_UI_H
#define _NET_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_network_bandwitdh_graph(WINDOW* main_page, 
                                net_t* network, 
                                const int time, 
                                const int intf_id, 
                                const int graph_width);

#endif /* _NET_UI_H */