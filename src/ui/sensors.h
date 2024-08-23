#ifndef _SENSORS_UI_H
#define _SENSORS_UI_H

#include "common.h"

#include "../logic/info/sys.h"

void print_sensors_page(WINDOW* main_page, 
                        sensor_t* sensor, 
                        const int time, 
                        const int cols);

#endif /* _SENSORS_UI_H */