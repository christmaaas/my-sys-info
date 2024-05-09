#include "net.h"

#include <stdlib.h>

#define SEC 10

void calculate_network_bandwidth(net_t* network, const int time, const int intf_id, const uint32_t graph_width)
{
    uint64_t r_bytes_at_moment = network->stat[intf_id].r_bytes;
    uint64_t t_bytes_at_moment = network->stat[intf_id].t_bytes;

    scan_network_stats(network); // refreshing data

    r_bytes_at_moment = network->stat[intf_id].r_bytes - r_bytes_at_moment;
    t_bytes_at_moment = network->stat[intf_id].t_bytes - t_bytes_at_moment;

    network->stat[intf_id].r_bandwith.cur = (double)r_bytes_at_moment / ((double)time / SEC);
    network->stat[intf_id].t_bandwith.cur = (double)t_bytes_at_moment / ((double)time / SEC);

    network->current_load[intf_id].r_load_history[network->current_load[intf_id].cur_point] = network->stat[intf_id].r_bandwith.cur;
    network->current_load[intf_id].t_load_history[network->current_load[intf_id].cur_point] = network->stat[intf_id].t_bandwith.cur;

    if (network->stat[intf_id].r_bandwith.cur > network->stat[intf_id].r_bandwith.max)
        network->stat[intf_id].r_bandwith.max = network->stat[intf_id].r_bandwith.cur;
    if (network->stat[intf_id].r_bandwith.cur < network->stat[intf_id].r_bandwith.min)
        network->stat[intf_id].r_bandwith.min = network->stat[intf_id].r_bandwith.cur;

    if (network->stat[intf_id].t_bandwith.cur > network->stat[intf_id].t_bandwith.max)
        network->stat[intf_id].t_bandwith.max = network->stat[intf_id].t_bandwith.cur;
    if (network->stat[intf_id].t_bandwith.cur < network->stat[intf_id].t_bandwith.min)
        network->stat[intf_id].t_bandwith.min = network->stat[intf_id].t_bandwith.cur;

    network->stat[intf_id].r_bandwith.avg = ((network->stat[intf_id].r_bandwith.avg * network->current_load[intf_id].cur_point) 
                                            + network->stat[intf_id].r_bandwith.cur) 
                                            / (network->current_load[intf_id].cur_point + 1);
    network->stat[intf_id].t_bandwith.avg = ((network->stat[intf_id].t_bandwith.avg * network->current_load[intf_id].cur_point) 
                                            + network->stat[intf_id].t_bandwith.cur) 
                                            / (network->current_load[intf_id].cur_point + 1);

    network->current_load[intf_id].cur_point++;

    if (network->current_load[intf_id].cur_point >= graph_width 
        || network->current_load[intf_id].cur_point >= MAX_NET_LOAD_HISTORY_SIZE)
    {
        for (uint32_t k = 0; k < graph_width - 1 && k < MAX_NET_LOAD_HISTORY_SIZE - 1; ++k)
        {
            network->current_load[intf_id].r_load_history[k] = network->current_load[intf_id].r_load_history[k + 1];
            network->current_load[intf_id].t_load_history[k] = network->current_load[intf_id].t_load_history[k + 1];
        }
        network->current_load[intf_id].cur_point = graph_width - 1;
    }
}

void init_network(net_t** network)
{
    *network = (net_t*)calloc(1, sizeof(net_t));
    
    init_network_interfaces(*network);
    scan_network_stats(*network);
}

void free_network(net_t* network)
{
    if (!network)
        return;

    free(network->stat);
    free(network->current_load);
    free(network);
}