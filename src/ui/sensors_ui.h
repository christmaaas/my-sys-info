#ifndef _SENSORS_UI_H
#define _SENSORS_UI_H

#include "common_ui.h"
#include "../logic/info/sys.h"

void print_sensors_page(WINDOW* main_page, sensor_t* sensor, int refresh_time, int current_cols);

#endif /* _SENSORS_UI_H */