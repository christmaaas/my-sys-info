#ifndef _NET_UTILS_H
#define _NET_UTILS_H

#include <stdint.h>

#define MAX_INTERFACE_NAME_LEN 	  30
#define MAX_NET_LOAD_HISTORY_SIZE 200

#define PATH_NETWORK_STATS_FILE "/proc/net/dev"

// r_ - received ; t_ - transmitted

typedef struct network_bandwidth
{
	double cur;
	double avg;
	double min;
	double max;
} netbandwidth_t;

typedef struct network_stats
{
	char           interface_name[MAX_INTERFACE_NAME_LEN];
	uint64_t       r_bytes;
	uint64_t       t_bytes;
	uint64_t       r_packets;
	uint64_t       t_packets;
	uint64_t       r_errs;
	uint64_t       t_errs;
	uint64_t       r_drop;
    uint64_t       t_drop;
	netbandwidth_t r_bandwith;
	netbandwidth_t t_bandwith;      
} netstat_t;

typedef struct net_load
{
    double   r_load_history[MAX_NET_LOAD_HISTORY_SIZE];
	double   t_load_history[MAX_NET_LOAD_HISTORY_SIZE];
    uint32_t cur_point;
} netload_t;

typedef struct network_info
{
    uint32_t   interfaces_num;
    netstat_t* stat;
	netload_t* current_load;
} net_t;

void init_network_interfaces(net_t* network);
void scan_network_stats(net_t* network);

#endif /* _NET_UTILS_H */