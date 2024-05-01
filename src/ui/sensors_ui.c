#include "sensors_ui.h"

#define GRAPH_BOUNDARY_OFFSET 3
#define SENSORS_GRAPH_OFFSET  38
#define INITIAL_GRAPH_OFFSET  37

void print_sensors_page(WINDOW* main_page, sensor_t* sensor, int refresh_time, int current_cols)
{
    PAGE("Sensors");

    calculate_sensors_stats(sensor);

    wattrset(main_page, COLOR_PAIR(25));
    mvwprintw(main_page, 0, 0, "Sensor name       |Cur°C|Max°C|Min°C|");
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 0, 41, "time: %0.1f sec", (double)refresh_time / SEC);

    for (uint32_t i = 0, l = 1; i < sensor->sensors_num; i++, l += 2)
	{
        wattrset(main_page, COLOR_PAIR(14));
        mvwprintw(main_page, l, 0, "%s", sensor->sensors[i].name);
        wattrset(main_page, COLOR_PAIR(15));
        mvwprintw_clr(main_page, l, 20, "%d", sensor->sensors[i].cur_temp);
        mvwprintw_clr(main_page, l, 26, "%d", sensor->sensors[i].max_temp);
        mvwprintw_clr(main_page, l, 32, "%d", sensor->sensors[i].min_temp);

		for (int j = 0; j < current_cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; j++)
		{
			if ((double)sensor->sensors[i].cur_temp / 100.0 * (current_cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET) > j + GRAPH_CORRECTION)
			{
				wattrset(main_page, COLOR_PAIR(8));
				mvwaddch(main_page, l, j + SENSORS_GRAPH_OFFSET, '|');
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(22));
				mvwaddch(main_page, l, j + SENSORS_GRAPH_OFFSET, ' ');
			}
		}
        wattrset(main_page, COLOR_PAIR(14));
		mvwprintw(main_page, l, INITIAL_GRAPH_OFFSET, "[");
		mvwprintw(main_page, l, current_cols - GRAPH_BOUNDARY_OFFSET, "]");

        wattrset(main_page, COLOR_PAIR(13));
        for (int k = 0; k < MAX_COLS_COUNT; k++) 
		    mvwaddch(main_page, l + 1, k, '-');
	}
    pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}