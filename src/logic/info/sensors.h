#ifndef _SENSORS_H
#define _SENSORS_H

#include "sensors_utils.h"

void init_sensors(sensor_t** sensor);
void free_sensors(sensor_t* sensor);
void calculate_sensors_stats(sensor_t* sensor);

#endif /* _SENSORS_H */