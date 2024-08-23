#include "sensors_utils.h"

#include "../../utils/file.h"
#include "../../utils/string.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#define CELTIUS 1000

void init_sensors_stats(sensor_t* sensor)
{
    sensor->sensors_num = get_count_of_files_name(PATH_SENSORS_DIR, "thermal_zone");
    sensor->stats       = (senstat_t*)calloc(sensor->sensors_num, sizeof(senstat_t));
}

void scan_sys_sensors_temp(sensor_t* sensor) 
{
    char cur_file_name[MAX_FILE_PATH_LEN];
    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/class/thermal/thermal_zone%d/temp", i);
        sensor->stats[i].cur_temp = get_file_int(cur_file_name) / CELTIUS; // to convert into Celtius
    }
}

void scan_sys_sensors_info(sensor_t* sensor)
{
    scan_sys_sensors_temp(sensor);
    
    char cur_file_name[MAX_FILE_PATH_LEN];
    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/class/thermal/thermal_zone%d/type", i);
        sensor->stats[i].name = get_file(cur_file_name);

        sensor->stats[i].min_temp = sensor->stats[i].cur_temp;
        // sensor->stats[i].max_temp is already set
    }
}