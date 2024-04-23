#ifndef _SENSORS_UTILS_H
#define _SENSORS_UTILS_H

#include <stdint.h>

#define PATH_SENSORS_DIR "/sys/class/thermal/"

typedef struct sensor_stat
{
    char*    name;
    uint16_t max_temp;
    uint16_t min_temp;
    uint16_t cur_temp;
} senstat_t;

typedef struct sensors_info
{
    uint32_t   sensors_num;
    senstat_t* sensors; 
} sensor_t;

void init_sensors_stats(sensor_t* sensor);
void scan_sys_sensors_info(sensor_t* sensor);
void scan_sys_sensors_temp(sensor_t* sensor);

#endif /* _SENSORS_UTILS_H */