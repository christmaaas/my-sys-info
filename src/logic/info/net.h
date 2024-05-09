#ifndef _NET_H
#define _NET_H

#include "net_utils.h"

void init_network(net_t** network);
void free_network(net_t* network);
void calculate_network_bandwidth(net_t* network, 
                                const int time, 
                                const int intf_id, 
                                const uint32_t graph_width);

#endif /* _NET_H */