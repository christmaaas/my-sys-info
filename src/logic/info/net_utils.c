#include "net_utils.h"
#include "../../utils/file_utils.h"

#include <stdio.h>
#include <stdlib.h>

void init_network_interfaces(net_t* network)
{
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(PATH_NETWORK_STATS_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"net_utils.c\" : init_net_interfaces()");
        return;
    }
    char file_buffer[FILE_BUFFER_SIZE];
    fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr);
    fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr);

    int interfaces_num = 0;
    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr)) 
        interfaces_num++;

    fclose(file_ptr);

    network->interfaces_num = interfaces_num;
    network->stat           = (netstat_t*)calloc(network->interfaces_num, sizeof(netstat_t));
    network->current_load   = (netload_t*)calloc(network->interfaces_num, sizeof(netload_t));
}

void scan_network_stats(net_t* network)
{
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(PATH_NETWORK_STATS_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"net_utils.c\" : scan_network_stats()");
        return;
    }
    char file_buffer[FILE_BUFFER_SIZE];
    fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr);
    fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr);

    int extra_field = 0;
    for (uint32_t i = 0; i < network->interfaces_num; i++) 
    {
        if(!fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr))
			break;
		sscanf(file_buffer, "%s %lu %lu %lu %lu %d %d %d %d %lu %lu %lu %lu",
		    network->stat[i].interface_name,
			&network->stat[i].r_bytes,
			&network->stat[i].r_packets,
			&network->stat[i].r_errs,
			&network->stat[i].r_drop,
			&extra_field,
			&extra_field,
			&extra_field,
			&extra_field,
			&network->stat[i].t_bytes,
			&network->stat[i].t_packets,
			&network->stat[i].t_errs,
			&network->stat[i].t_drop);
	}
    fclose(file_ptr);
}
