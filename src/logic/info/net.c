#include "net.h"

#include <stdlib.h>

#define SEC 10

void calculate_network_bandwidth(net_t* network, int refresh_time, int intf, int graph_points_num)
{
    uint64_t r_bytes_at_moment = network->stat[intf].r_bytes;
    uint64_t t_bytes_at_moment = network->stat[intf].t_bytes;

    scan_network_stats(network);

    r_bytes_at_moment = network->stat[intf].r_bytes - r_bytes_at_moment;
    t_bytes_at_moment = network->stat[intf].t_bytes - t_bytes_at_moment;

    network->stat[intf].r_bandwith.cur = (double)r_bytes_at_moment / ((double)refresh_time / SEC);
    network->stat[intf].t_bandwith.cur = (double)t_bytes_at_moment / ((double)refresh_time / SEC);

    network->current_load[intf].r_load_history[network->current_load[intf].cur_point] = network->stat[intf].r_bandwith.cur;
    network->current_load[intf].t_load_history[network->current_load[intf].cur_point] = network->stat[intf].t_bandwith.cur;

    if (network->stat[intf].r_bandwith.cur > network->stat[intf].r_bandwith.max)
        network->stat[intf].r_bandwith.max = network->stat[intf].r_bandwith.cur;
    if (network->stat[intf].r_bandwith.cur < network->stat[intf].r_bandwith.min)
        network->stat[intf].r_bandwith.min = network->stat[intf].r_bandwith.cur;

    if (network->stat[intf].t_bandwith.cur > network->stat[intf].t_bandwith.max)
        network->stat[intf].t_bandwith.max = network->stat[intf].t_bandwith.cur;
    if (network->stat[intf].t_bandwith.cur < network->stat[intf].t_bandwith.min)
        network->stat[intf].t_bandwith.min = network->stat[intf].t_bandwith.cur;

    network->stat[intf].r_bandwith.avg = ((network->stat[intf].r_bandwith.avg * network->current_load[intf].cur_point) 
                                            + network->stat[intf].r_bandwith.cur) 
                                            / (network->current_load[intf].cur_point + 1);
    network->stat[intf].t_bandwith.avg = ((network->stat[intf].t_bandwith.avg * network->current_load[intf].cur_point) 
                                            + network->stat[intf].t_bandwith.cur) 
                                            / (network->current_load[intf].cur_point + 1);

    network->current_load[intf].cur_point++;

    if (network->current_load[intf].cur_point >= graph_points_num 
        || network->current_load[intf].cur_point >= MAX_NET_LOAD_HISTORY_SIZE)
    {
        for (int k = 0; k < graph_points_num - 1 && k < MAX_NET_LOAD_HISTORY_SIZE - 1; ++k)
        {
            network->current_load[intf].r_load_history[k] = network->current_load[intf].r_load_history[k + 1];
            network->current_load[intf].t_load_history[k] = network->current_load[intf].t_load_history[k + 1];
        }
        network->current_load[intf].cur_point = graph_points_num - 1;
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