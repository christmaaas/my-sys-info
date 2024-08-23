#include "sensors.h"

#define GRAPH_BOUNDARY_OFFSET 3
#define SENSORS_GRAPH_OFFSET  38
#define INITIAL_GRAPH_OFFSET  37

void print_sensors_page(WINDOW* main_page, sensor_t* sensor, const int time, const int cols)
{
    PAGE_TITLE("Sensors Info");

    calculate_sensors_stats(sensor);

    wattrset(main_page, COLOR_PAIR(PAIR_WHITE_BLUE));
	wattron(main_page, A_BOLD);
    mvwprintw(main_page, 0, 0, "Sensor name       |Cur°C|Max°C|Min°C|");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 0, 41, "time: %0.1f sec", (double)time / SEC);
	wattroff(main_page, A_BOLD);

    for (uint32_t i = 0, l = 1; i < sensor->sensors_num; i++, l += 2)
	{
        wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
        mvwprintw(main_page, l, 0, "%s", sensor->stats[i].name);
		
        wattrset(main_page, COLOR_PAIR(PAIR_RED_WHITE));
        mvwprintw_clr(main_page, l, 20, "%d", sensor->stats[i].cur_temp);
        mvwprintw_clr(main_page, l, 26, "%d", sensor->stats[i].max_temp);
        mvwprintw_clr(main_page, l, 32, "%d", sensor->stats[i].min_temp);

		for (int j = 0; j < cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; j++)
		{
			if ((double)sensor->stats[i].cur_temp / 100.0 
				* (cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET) > j + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_RED));
				mvwaddch(main_page, l, j + SENSORS_GRAPH_OFFSET, '|');
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(PAIR_GREEN_GREEN));
				mvwaddch(main_page, l, j + SENSORS_GRAPH_OFFSET, ' ');
			}
		}
        wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwprintw(main_page, l, INITIAL_GRAPH_OFFSET, "[");
		mvwprintw(main_page, l, cols - GRAPH_BOUNDARY_OFFSET, "]");

        wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
        for (int k = 0; k < MAX_COLS_COUNT; k++) 
		    mvwaddch(main_page, l + 1, k, '-');
	}
    pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}