#include "mem.h"

#define NUMBER_OF_MEMORY_GRAPHS 6
#define LOAD_LINE_START_POINT 	0
#define DIAGRAM_SIZE			50
#define DIAGRAM_START_POINT		27

void print_memory_page(WINDOW* main_page, mem_t* memory)
{
	PAGE_TITLE("Memory Info");

	calculate_memory_usage_percentage(memory);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 0, 0, "Pages:");
	mvwprintw(main_page, 1, 0, "Anon pages: ");
	mvwprintw(main_page, 2, 0, "Page tables: ");

	wattrset(main_page, COLOR_PAIR(PAIR_CYAN_BLUE));
	mvwprintw_clr(main_page, 1, 13, "%.1fMiB", memory->usage_stats.anon_pages / KiB);
	mvwprintw_clr(main_page, 2, 13, "%.1fMiB", memory->usage_stats.page_tables / KiB);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 0, 25, "Activity:");
	mvwprintw(main_page, 1, 25, "Active: ");
	mvwprintw(main_page, 2, 25, "Inactive: ");

	wattrset(main_page, COLOR_PAIR(PAIR_CYAN_BLUE));
	mvwprintw_clr(main_page, 1, 35, "%.1fMiB", memory->usage_stats.active / KiB);
	mvwprintw_clr(main_page, 2, 35, "%.1fMiB", memory->usage_stats.inactive / KiB);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 1, 47, "Shared: ");
	mvwprintw(main_page, 2, 47, "Mapped: ");

	wattrset(main_page, COLOR_PAIR(PAIR_CYAN_BLUE));
	mvwprintw_clr(main_page, 1, 55, "%.1fMiB", memory->usage_stats.shmem / KiB);
	mvwprintw_clr(main_page, 2, 55, "%.1fMiB", memory->usage_stats.mapped / KiB);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 3, 0, "RAM (%.1fMiB Total):", memory->usage_stats.total / KiB);
	mvwprintw_clr(main_page, 15, 0, "Swap (%.1fMiB Total):", memory->usage_stats.swap_total / KiB);
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 4, 0, "Utilization:");

	wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_WHITE));
	mvwprintw_clr(main_page, 5, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.usage / KiB, 
														memory->usage_percentage.usage);
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 7, 0, "Buffers:");

	wattrset(main_page, COLOR_PAIR(PAIR_MAGENDA_WHITE));
	mvwprintw_clr(main_page, 8, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.buffers / KiB,
														memory->usage_percentage.buffers);
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 10, 0, "Cached:");

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 11, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.cached / KiB,
														memory->usage_percentage.cached);
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 13, 0, "Free:");

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_WHITE));
	mvwprintw_clr(main_page, 14, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.free / KiB,
														memory->usage_percentage.free);
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 16, 0, "Utilization:");

	wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_WHITE));
	mvwprintw_clr(main_page, 17, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.swap_usage / KiB,
														memory->usage_percentage.swap_usage);
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 19, 0, "Free:");

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_WHITE));
	mvwprintw_clr(main_page, 20, 0, "%.1fMiB(%3.1lf%%)", memory->usage_stats.swap_free / KiB,
														memory->usage_percentage.swap_free);
	wmove(main_page, LOAD_LINE_START_POINT + 5, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.usage / 2)); i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_YELLOW));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 8, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.buffers) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_MAGENDA_MAGENDA));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 11, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.cached) / 2); i++)
	{		
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_BLUE));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 14, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.free) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_GREEN_GREEN));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 17, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.swap_usage) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_YELLOW));
		wprintw(main_page, " ");
	}
	wmove(main_page, LOAD_LINE_START_POINT + 20, DIAGRAM_START_POINT + 1);
	for (int i = 0; i < (int)((memory->usage_percentage.swap_free) / 2); i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_GREEN_GREEN));
		wprintw(main_page, " ");
	}
	for (int i = 0; i < NUMBER_OF_MEMORY_GRAPHS * 3; i += 3) // += 3 to skip extra fields of next graph frame
	{
		wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
		mvwaddch(main_page, i + 3, DIAGRAM_START_POINT, ACS_PLUS);
		mvwaddch(main_page, i + 3, DIAGRAM_START_POINT + DIAGRAM_SIZE, ACS_PLUS);
		for (int k = 1; k < DIAGRAM_SIZE; k++)
			mvwaddch(main_page, i + 3, k + DIAGRAM_START_POINT, ACS_HLINE);

		mvwaddch(main_page, i + 4, DIAGRAM_START_POINT, ACS_VLINE);
		mvwaddch(main_page, i + 4, DIAGRAM_START_POINT + DIAGRAM_SIZE, ACS_VLINE);
		mvwprintw(main_page, i + 4, DIAGRAM_START_POINT + 1, "0%%");
		mvwprintw(main_page, i + 4, DIAGRAM_START_POINT + DIAGRAM_SIZE - 4, "100%%");

		mvwaddch(main_page, i + 5, DIAGRAM_START_POINT, ACS_VLINE);
		mvwaddch(main_page, i + 5, DIAGRAM_START_POINT + DIAGRAM_SIZE, ACS_VLINE);
	}
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwaddch(main_page, 21, DIAGRAM_START_POINT, ACS_PLUS);
	mvwaddch(main_page, 21, DIAGRAM_START_POINT + DIAGRAM_SIZE, ACS_PLUS);
	for (int k = 1; k < DIAGRAM_SIZE; k++)
		mvwaddch(main_page, 21, k + DIAGRAM_START_POINT, ACS_HLINE);

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define MAX_RAM_GRAPH_HEIGHT  9
#define MAX_SWAP_GRAPH_HEIGHT 9

void print_memory_load_graph(WINDOW* main_page, mem_t* memory, const int time, const int graph_width)
{
	PAGE_TITLE("Memory Usage");

	calculate_total_memory_load(memory, graph_width);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 1, 0, "100%%");
    mvwprintw(main_page, 12, 0, "100%%");
	mvwprintw(main_page, 10, 2, "0%%");
	mvwprintw(main_page, 21, 2, "0%%");

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 0, 0, "RAM usage/time graph | time: %0.1f sec", (double)time / SEC);
	mvwprintw_clr(main_page, 11, 0, "Swap usage/time graph | time: %0.1f sec", (double)time / SEC);
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_YELLOW));
	mvwprintw(main_page, 0, 45, " ");

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_GREEN));
	mvwprintw(main_page, 11, 45, " ");
	
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 0, 46, " - current RAM usage");
	mvwprintw(main_page, 11, 46, " - current Swap usage");
	wattroff(main_page, A_BOLD);

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_RAM_GRAPH_HEIGHT; y++) 
		{
			if (y == 1)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((memory->current_load.ram_load_history[x]) / 100.0 * MAX_RAM_GRAPH_HEIGHT > y + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_YELLOW));
				mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_BLACK));
				mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwaddch(main_page, MAX_RAM_GRAPH_HEIGHT + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
    for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_SWAP_GRAPH_HEIGHT; y++) 
		{
			if (y == GRAPH_BOTTOM_BOUND - 12)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - 8, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((memory->current_load.swap_load_history[x]) / 100.0 * MAX_SWAP_GRAPH_HEIGHT > y + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_GREEN));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_BLACK));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwaddch(main_page, GRAPH_BOTTOM_BOUND + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}