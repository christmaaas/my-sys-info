#include "mem_ui.h"

#define NUMBER_OF_MEMORY_GRAPHS 6
#define LOAD_LINE_START_POINT 	0

void print_memory_page(WINDOW* main_page, system_t* data)
{
	PAGE("Memory Usage"); 

	calculate_memory_usage_percentage(data->memory);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 0,  0, "Pages:");
	mvwprintw(main_page, 1,  0, "Anon pages: ");
	mvwprintw(main_page, 2,  0, "Page tables: ");
	wattrset(main_page, COLOR_PAIR(26));
	mvwprintw_clr(main_page, 1,  13, "%.1fMB", data->memory->memory_usage.anon_pages / 1024.0);
	mvwprintw_clr(main_page, 2,  13, "%.1fMB", data->memory->memory_usage.page_tables / 1024.0);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 0,  25, "Activity:");
	mvwprintw(main_page, 1,  25, "Active: ");
	mvwprintw(main_page, 2,  25, "Inactive: ");
	wattrset(main_page, COLOR_PAIR(26));
	mvwprintw_clr(main_page, 1,  35, "%.1fMB", data->memory->memory_usage.active / 1024.0);
	mvwprintw_clr(main_page, 2,  35, "%.1fMB", data->memory->memory_usage.inactive / 1024.0);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1,  47, "Shared: ");
	mvwprintw(main_page, 2,  47, "Mapped: ");
	wattrset(main_page, COLOR_PAIR(26));
	mvwprintw_clr(main_page, 1,  55, "%.1fMB", data->memory->memory_usage.shmem / 1024.0);
	mvwprintw_clr(main_page, 2,  55, "%.1fMB", data->memory->memory_usage.mapped / 1024.0);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 3,  0, "RAM (%.1fMB Total)", data->memory->memory_usage.total / 1024.0);
	mvwprintw_clr(main_page, 15,  0, "Swap (%.1fMB Total)", data->memory->memory_usage.swap_total / 1024.0);

	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 4, 0, "Usage");
	wattrset(main_page, COLOR_PAIR(17));
	mvwprintw_clr(main_page, 5, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.usage / 1024.0, 
														data->memory->memory_percentage.usage);
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 7, 0, "Buffers");
	wattrset(main_page, COLOR_PAIR(19));
	mvwprintw_clr(main_page, 8, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.buffers / 1024.0,
														data->memory->memory_percentage.buffers);
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 10, 0, "Cached");
	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 11, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.cached / 1024.0,
														 data->memory->memory_percentage.cached);
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 13, 0, "Free");
	wattrset(main_page, COLOR_PAIR(16));
	mvwprintw_clr(main_page, 14, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.free / 1024.0,
														 data->memory->memory_percentage.free);
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 16, 0, "Usage");
	wattrset(main_page, COLOR_PAIR(17));
	mvwprintw_clr(main_page, 17, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.swap_usage / 1024.0,
														 data->memory->memory_percentage.swap_usage);
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 19, 0, "Free");
	wattrset(main_page, COLOR_PAIR(16));
	mvwprintw_clr(main_page, 20, 0, "%.1fMB(%3.1lf%%)", data->memory->memory_usage.swap_free / 1024.0,
														 data->memory->memory_percentage.swap_free);
	wmove(main_page, LOAD_LINE_START_POINT + 5, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.usage / 2)); i++)
	{
		wattrset(main_page, COLOR_PAIR(21));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 8, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.buffers) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(20));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 11, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.cached) / 2); i++)
	{		
		wattrset(main_page, COLOR_PAIR(23));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 14, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.free) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(22));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 17, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.swap_usage) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(20));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 20, 28);
	for (int i = 0; i < (int)((data->memory->memory_percentage.swap_free) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(22));
		wprintw(main_page, " ");
	}
	for (int i = 0; i < NUMBER_OF_MEMORY_GRAPHS * 3; i += 3) // i += 3 to skip extra fields of next graph frame
	{
		wattrset(main_page, COLOR_PAIR(13));
		mvwprintw(main_page, i + 3, 27, "+-------------------------------------------------+");
		mvwprintw(main_page, i + 4, 27, "|0%%         |25%%        |50%%         |75%%     100%%|");
		mvwprintw(main_page, i + 5, 27, "|");
		mvwprintw(main_page, i + 5, 77, "|");
	}
	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 21, 27, "+-------------------------------------------------+");

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define MAX_RAM_GRAPH_HEIGHT	 9
#define MAX_SWAP_GRAPH_HEIGHT	 9
#define SWAP_GRAPH_BOTTOM_BOUND	 20
#define GRAPH_POINT_OFFSET 	 	 6
#define GRAPH_DELIM_LINE_OFFSET  4

void print_memory_load_graph(WINDOW* main_page, system_t* data, int refresh_time)
{
	PAGE("Memory Load");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 0, "100%%");
    mvwprintw(main_page, 12, 0, "100%%");
	mvwprintw(main_page, 10, 1, "<5%%");
	mvwprintw(main_page, 21, 1, "<5%%");

	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw_clr(main_page, 0, 0, "RAM/time graph | time: %0.1f sec", (double)refresh_time / 10);
	mvwprintw_clr(main_page, 11, 0, "Swap/time graph | time: %0.1f sec", (double)refresh_time / 10);
	wattrset(main_page, COLOR_PAIR(21));
	mvwprintw(main_page, 0, 45, " ");
	wattrset(main_page, COLOR_PAIR(22));
	mvwprintw(main_page, 11, 45, " ");
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 0, 46, " - current RAM load");
	mvwprintw(main_page, 11, 46, " - current Swap load");

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_RAM_GRAPH_HEIGHT; y++) 
		{
			if (y == 1)
			{
				wattrset(main_page, COLOR_PAIR(14));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((data->memory->current_load.ram_load_history[x]) / 100 * MAX_RAM_GRAPH_HEIGHT > y + 0.5)
			{
				wattrset(main_page, COLOR_PAIR(11));
				mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(0));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(4));
				mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(14));
		mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
    for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_SWAP_GRAPH_HEIGHT; y++) 
		{
			if (y == SWAP_GRAPH_BOTTOM_BOUND - 12)
			{
				wattrset(main_page, COLOR_PAIR(14));
				mvwaddch(main_page, SWAP_GRAPH_BOTTOM_BOUND - 8, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((data->memory->current_load.swap_load_history[x]) / 100 * MAX_SWAP_GRAPH_HEIGHT > y + 0.5)
			{
				wattrset(main_page, COLOR_PAIR(9));
				mvwaddch(main_page, SWAP_GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(0));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(4));
				mvwaddch(main_page, SWAP_GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(14));
		mvwaddch(main_page, SWAP_GRAPH_BOTTOM_BOUND + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}