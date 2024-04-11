#include "net_ui.h"

#define MAX_NETWORK_GRAPH_HEIGHT 12  

void print_network_bandwitdh_graph(WINDOW* main_page, net_t* network, int refresh_time, int selected_intf)
{
	PAGE("Network Bandwidth");

	wattrset(main_page, COLOR_PAIR(25));
    mvwprintw_clr(main_page, 0, 0, "Interface %s (%d/%d)", network->stat[selected_intf].interface_name, selected_intf + 1, network->interfaces_num);
	wattrset(main_page, COLOR_PAIR(14));
	for (int i = 0; i < MAX_COLS_COUNT; i++) 
		mvwaddch(main_page, 1, i, '=');
    
	wattrset(main_page, COLOR_PAIR(34));
    mvwprintw(main_page, 2, 0, "Received:");
	wattrset(main_page, COLOR_PAIR(14));
    mvwprintw_clr(main_page, 3, 0, "Curr: %0.2f kBit/s", network->stat[selected_intf].r_bandwith.cur / KB);
    mvwprintw_clr(main_page, 4, 0, "Avg:  %0.2f kBit/s", network->stat[selected_intf].r_bandwith.avg / KB);
    mvwprintw_clr(main_page, 5, 0, "Min:  %0.2f kBit/s", network->stat[selected_intf].r_bandwith.min / KB);
    mvwprintw_clr(main_page, 6, 0, "Max:  %0.2f kBit/s", network->stat[selected_intf].r_bandwith.max / KB);
    mvwprintw_clr(main_page, 7, 0, "Ttl:  %0.2f MByte", network->stat[selected_intf].r_bytes / MB);

	wattrset(main_page, COLOR_PAIR(33));
    mvwprintw(main_page, 2, 25, "Transmitted:");
	wattrset(main_page, COLOR_PAIR(14));
    mvwprintw_clr(main_page, 3, 25, "Curr: %0.2f kBit/s", network->stat[selected_intf].t_bandwith.cur / KB);
    mvwprintw_clr(main_page, 4, 25, "Avg:  %0.2f kBit/s", network->stat[selected_intf].t_bandwith.avg / KB);
    mvwprintw_clr(main_page, 5, 25, "Min:  %0.2f kBit/s", network->stat[selected_intf].t_bandwith.min / KB);
    mvwprintw_clr(main_page, 6, 25, "Max:  %0.2f kBit/s", network->stat[selected_intf].t_bandwith.max / KB);
    mvwprintw_clr(main_page, 7, 25, "Ttl:  %0.2f MByte", network->stat[selected_intf].t_bytes / MB);

	mvwprintw_clr(main_page, 2, 50, "Received pkg:  %lu", network->stat[selected_intf].r_packets);
    mvwprintw_clr(main_page, 3, 50, "Received errs: %lu", network->stat[selected_intf].r_errs);
    mvwprintw_clr(main_page, 4, 50, "Received drop: %lu", network->stat[selected_intf].r_drop);
    mvwprintw_clr(main_page, 5, 50, "Transmitted pkg:  %lu", network->stat[selected_intf].t_packets);
    mvwprintw_clr(main_page, 6, 50, "Transmitted errs: %lu", network->stat[selected_intf].t_errs);
    mvwprintw_clr(main_page, 7, 50, "Transmitted drop: %lu", network->stat[selected_intf].t_drop);

	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw_clr(main_page, 8, 0, "Network Bandwitdh/time graph | time: %0.1f sec", (double)refresh_time / 10);
	wattrset(main_page, COLOR_PAIR(32));
	mvwprintw(main_page, 8, 47, " ");
	wattrset(main_page, COLOR_PAIR(31));
	mvwprintw(main_page, 8, 60, " ");
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 8, 48, " - Received");
	mvwprintw(main_page, 8, 61, " - Transmitted");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 9, 1, "Max");
	mvwprintw(main_page, 21, 0, "0B/s");

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_NETWORK_GRAPH_HEIGHT; y++) 
		{
			if (y == GRAPH_BOTTOM_BOUND - 11)
			{
				wattrset(main_page, COLOR_PAIR(14));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			wattrset(main_page, COLOR_PAIR(2));
			mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			
			if ((network->current_load[selected_intf].r_load_history[x]) 
					/ network->stat[selected_intf].r_bandwith.max * MAX_NETWORK_GRAPH_HEIGHT > y + GRAPH_CORRECTION)
			{
				wattrset(main_page, COLOR_PAIR(12));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(0));
			}
			if ((network->current_load[selected_intf].t_load_history[x]) 
					/ network->stat[selected_intf].r_bandwith.max * MAX_NETWORK_GRAPH_HEIGHT > y)
			{
				wattrset(main_page, COLOR_PAIR(8));
				mvwaddch(main_page, GRAPH_BOTTOM_BOUND - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(0));
			}
		}
		wattrset(main_page, COLOR_PAIR(14));
		mvwaddch(main_page, GRAPH_BOTTOM_BOUND + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}