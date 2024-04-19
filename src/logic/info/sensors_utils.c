#include "sensors_utils.h"

#include "../../utils/file_utils.h"
#include "../../utils/string_utils.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void init_sensors_stats(sensor_t* sensor)
{
    sensor->sensors_num = get_count_of_files_name(PATH_SENSORS_DIR, "thermal_zone");
    sensor->sensors     = (senstat_t*)calloc(sensor->sensors_num, sizeof(senstat_t));
}

void scan_sys_sensors_temp(sensor_t* sensor) 
{
    char cur_file_name[MAX_FILE_PATH_LEN];
    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/class/thermal/thermal_zone%d/temp", i);
        sensor->sensors[i].cur_temp = get_file_int(cur_file_name) / 1000; // devision by 1000 to convert to Celtius
    }
}

void scan_sys_sensors_info(sensor_t* sensor)
{
    char cur_file_name[MAX_FILE_PATH_LEN];
    for (uint32_t i = 0; i < sensor->sensors_num; i++)
    {
        snprintf(cur_file_name, MAX_FILE_PATH_LEN, "/sys/class/thermal/thermal_zone%d/type", i);
        sensor->sensors[i].name = get_file(cur_file_name);

        scan_sys_sensors_temp(sensor);
        sensor->sensors[i].min_temp = sensor->sensors[i].cur_temp;
        sensor->sensors[i].max_temp = sensor->sensors[i].cur_temp;
    }
}