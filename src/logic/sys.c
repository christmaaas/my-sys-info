#include "sys.h"

#include <stdlib.h>

void init_system_data(system_t** data)
{
    *data = (system_t*)calloc(1, sizeof(system_t));
    
    init_cpu(&((*data)->cpu));
    init_memory(&((*data)->memory));

    // ...
}

void free_system_data(system_t* data)
{
    if (!data)
        return;
    
    free_cpu(data->cpu);
    free_memory(data->memory);

    // ...

    free(data);
}