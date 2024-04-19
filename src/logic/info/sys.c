#include "sys.h"

#include <stdlib.h>

void init_system_data(system_t** data)
{
    *data = (system_t*)calloc(1, sizeof(system_t));
    
    init_cpu(&((*data)->cpu));
    init_memory(&((*data)->memory));
    init_network(&((*data)->network));
    init_pci(&((*data)->pci));
    init_sensors(&((*data)->sensor));

    // ...
}

void free_system_data(system_t* data)
{
    if (!data)
        return;
    
    free_cpu(data->cpu);
    free_memory(data->memory);
    free_network(data->network);
    free_pci(data->pci);
    free_sensors(data->sensor);

    // ...

    free(data);
}