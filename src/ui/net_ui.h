#ifndef _NET_UI_H
#define _NET_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_network_bandwitdh_graph(WINDOW* main_page, net_t* network, int refresh_time, int selected_intf, int graph_points_num);

#endif /* _NET_UI_H */