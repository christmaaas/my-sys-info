#ifndef _NET_H
#define _NET_H

#include "net_utils.h"

void init_network(net_t** network);
void free_network(net_t* network);
void calculate_network_bandwidth(net_t* network, int refresh_time, int intf, int graph_points_num);

#endif /* _NET_H */