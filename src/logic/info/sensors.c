#include "sensors.h"

#include <stdlib.h>

void init_sensors(sensor_t** sensor)
{
    *sensor = (sensor_t*)calloc(1, sizeof(sensor_t));
    
    init_sensors_stats(*sensor);
    scan_sys_sensors_info(*sensor);
}

void calculate_sensors_stats(sensor_t* sensor)
{
    uint16_t* sensors_min_temp = (uint16_t*)calloc(sensor->sensors_num, sizeof(uint16_t));
    uint16_t* sensors_max_temp = (uint16_t*)calloc(sensor->sensors_num, sizeof(uint16_t));

    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        sensors_min_temp[i] = sensor->sensors[i].min_temp;
        sensors_max_temp[i] = sensor->sensors[i].max_temp;
    }

    scan_sys_sensors_temp(sensor);

    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        if (sensor->sensors[i].cur_temp < sensors_min_temp[i])
            sensor->sensors[i].min_temp = sensor->sensors[i].cur_temp;
        if (sensor->sensors[i].cur_temp > sensors_max_temp[i])
            sensor->sensors[i].max_temp = sensor->sensors[i].cur_temp;
    }

    free(sensors_min_temp);
    free(sensors_max_temp);
}

void free_sensors(sensor_t* sensor)
{
    if (!sensor)
        return;
        
    for (uint32_t sen = 0; sen < sensor->sensors_num; sen++)
        free(sensor->sensors[sen].name);

    free(sensor->sensors);
    free(sensor);
}