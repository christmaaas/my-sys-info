#include "net_ui.h"

#define MAX_NETWORK_GRAPH_HEIGHT 12  

void print_network_bandwitdh_graph(WINDOW* main_page, net_t* network, const int time, const int intf_id, const int graph_width)
{
	wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
	mvprintw(0, PAGE_TITLE_OFFSET, "Network Bandwidth");
	wnoutrefresh(stdscr);

	calculate_network_bandwidth(network, time, intf_id, graph_width);

	wattrset(main_page, COLOR_PAIR(PAIR_WHITE_BLUE));
    mvwprintw_clr(main_page, 0, 0, "Interface %s (%d/%d)", network->stat[intf_id].interface_name, intf_id + 1, network->interfaces_num);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	for (int i = 0; i < MAX_COLS_COUNT; i++) 
		mvwaddch(main_page, 1, i, '=');
    
	wattrset(main_page, COLOR_PAIR(PAIR_WHITE_CYAN));
	wattron(main_page, A_BOLD);
    mvwprintw(main_page, 2, 0, "Received:");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
    mvwprintw_clr(main_page, 3, 0, "Cur: %0.2f KiB/s", network->stat[intf_id].r_bandwith.cur / KiB);
    mvwprintw_clr(main_page, 4, 0, "Avg: %0.2f KiB/s", network->stat[intf_id].r_bandwith.avg / KiB);
    mvwprintw_clr(main_page, 5, 0, "Min: %0.2f KiB/s", network->stat[intf_id].r_bandwith.min / KiB);
    mvwprintw_clr(main_page, 6, 0, "Max: %0.2f KiB/s", network->stat[intf_id].r_bandwith.max / KiB);
    mvwprintw_clr(main_page, 7, 0, "Ttl: %0.2f MiB", network->stat[intf_id].r_bytes / MiB);

	wattrset(main_page, COLOR_PAIR(PAIR_WHITE_RED));
	wattron(main_page, A_BOLD);
    mvwprintw(main_page, 2, 25, "Transmitted:");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
    mvwprintw_clr(main_page, 3, 25, "Cur: %0.2f KiB/s", network->stat[intf_id].t_bandwith.cur / KiB);
    mvwprintw_clr(main_page, 4, 25, "Avg: %0.2f KiB/s", network->stat[intf_id].t_bandwith.avg / KiB);
    mvwprintw_clr(main_page, 5, 25, "Min: %0.2f KiB/s", network->stat[intf_id].t_bandwith.min / KiB);
    mvwprintw_clr(main_page, 6, 25, "Max: %0.2f KiB/s", network->stat[intf_id].t_bandwith.max / KiB);
    mvwprintw_clr(main_page, 7, 25, "Ttl: %0.2f MiB", network->stat[intf_id].t_bytes / MiB);

	mvwprintw_clr(main_page, 2, 50, "Received pkg:  %lu", network->stat[intf_id].r_packets);
    mvwprintw_clr(main_page, 3, 50, "Received errs: %lu", network->stat[intf_id].r_errs);
    mvwprintw_clr(main_page, 4, 50, "Received drop: %lu", network->stat[intf_id].r_drop);
    mvwprintw_clr(main_page, 5, 50, "Transmitted pkg:  %lu", network->stat[intf_id].t_packets);
    mvwprintw_clr(main_page, 6, 50, "Transmitted errs: %lu", network->stat[intf_id].t_errs);
    mvwprintw_clr(main_page, 7, 50, "Transmitted drop: %lu", network->stat[intf_id].t_drop);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 8, 0, "Network bandwitdh/time graph | time: %0.1f sec", (double)time / SEC);
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_CYAN_CYAN));
	mvwprintw(main_page, 8, 47, " ");

	wattrset(main_page, COLOR_PAIR(PAIR_RED_RED));
	mvwprintw(main_page, 8, 60, " ");
	
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 8, 48, " - Received");
	mvwprintw(main_page, 8, 61, " - Transmitted");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 9, 1, "Max");
	mvwprintw(main_page, 21, 0, "0KiB");

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_NETWORK_GRAPH_HEIGHT; y++) 
		{
			if (y == GRAPH_BOTTOM_BOUND - 11)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			wattrset(main_page, COLOR_PAIR(PAIR_GREEN_BLACK));
			mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			
			if ((network->current_load[intf_id].r_load_history[x]) 
					/ network->stat[intf_id].r_bandwith.max * MAX_NETWORK_GRAPH_HEIGHT > y + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_CYAN));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			}
			if ((network->current_load[intf_id].t_load_history[x]) 
					/ network->stat[intf_id].r_bandwith.max * MAX_NETWORK_GRAPH_HEIGHT > y)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_RED));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			}
		}
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwaddch(main_page, GRAPH_BOTTOM_BOUND + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}