#include "../logic/info/sys.h"
#include "../logic/report/report.h"
#include "main_ui.h"
#include "cpu_ui.h"
#include "mem_ui.h"
#include "net_ui.h"
#include "time_ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>

int current_lines;
int current_cols;

uint32_t selected_processor_id = 0;
uint32_t selected_intf = 0;

int active_page = P_DEFAULT;
int prev_page;

int refresh_time = 10; // in milliseconds

WINDOW *main_page;
system_t *data;

void init_pairs(int color)
{
	if (color)
	{
		init_pair((short)0, (short)COLOR_WHITE, (short)COLOR_BLACK);
		init_pair((short)1, (short)COLOR_RED, (short)COLOR_BLACK);
		init_pair((short)2, (short)COLOR_GREEN, (short)COLOR_BLACK);
		init_pair((short)3, (short)COLOR_YELLOW, (short)COLOR_BLACK);
		init_pair((short)4, (short)COLOR_BLUE, (short)COLOR_BLACK);
		init_pair((short)5, (short)COLOR_MAGENTA, (short)COLOR_BLACK);
		init_pair((short)6, (short)COLOR_CYAN, (short)COLOR_BLACK);
		init_pair((short)7, (short)COLOR_WHITE, (short)COLOR_BLACK);
		init_pair((short)8, (short)COLOR_BLACK, (short)COLOR_RED);
		init_pair((short)9, (short)COLOR_BLACK, (short)COLOR_GREEN);
		init_pair((short)10, (short)COLOR_BLACK, (short)COLOR_BLUE);
		init_pair((short)11, (short)COLOR_BLACK, (short)COLOR_YELLOW);
		init_pair((short)12, (short)COLOR_BLACK, (short)COLOR_CYAN);
		init_pair((short)13, (short)COLOR_BLACK, (short)COLOR_WHITE);
		init_pair((short)14, (short)COLOR_BLUE, (short)COLOR_WHITE);
		init_pair((short)15, (short)COLOR_RED, (short)COLOR_WHITE);
		init_pair((short)16, (short)COLOR_GREEN, (short)COLOR_WHITE);
		init_pair((short)17, (short)COLOR_YELLOW, (short)COLOR_WHITE);
		init_pair((short)18, (short)COLOR_RED, (short)COLOR_GREEN);
		init_pair((short)19, (short)COLOR_MAGENTA, (short)COLOR_WHITE);
		init_pair((short)20, (short)COLOR_MAGENTA, (short)COLOR_MAGENTA);
		init_pair((short)21, (short)COLOR_YELLOW, (short)COLOR_YELLOW);
		init_pair((short)22, (short)COLOR_GREEN, (short)COLOR_GREEN);
		init_pair((short)23, (short)COLOR_BLUE, (short)COLOR_BLUE);
		init_pair((short)24, (short)COLOR_WHITE, (short)COLOR_CYAN);
		init_pair((short)25, (short)COLOR_WHITE, (short)COLOR_BLUE);
		init_pair((short)26, (short)COLOR_CYAN, (short)COLOR_BLUE);
		init_pair((short)27, (short)COLOR_GREEN, (short)COLOR_BLUE);
		init_pair((short)28, (short)COLOR_RED, (short)COLOR_BLUE);
		init_pair((short)29, (short)COLOR_YELLOW, (short)COLOR_BLUE);
		init_pair((short)30, (short)COLOR_BLUE, (short)COLOR_YELLOW);
		init_pair((short)31, (short)COLOR_RED, (short)COLOR_RED);
		init_pair((short)32, (short)COLOR_CYAN, (short)COLOR_CYAN);
		init_pair((short)33, (short)COLOR_WHITE, (short)COLOR_RED);
		init_pair((short)34, (short)COLOR_WHITE, (short)COLOR_CYAN);
	}
}

int check_window_resize(int* prev_lines, int* prev_cols)
{
	wrefresh(stdscr);
	if (*prev_lines != LINES || *prev_cols != COLS)
	{
		*prev_lines = LINES;
		*prev_cols = COLS;
		return 0;
	}
	return 1;
}

int check_time_changed(int* current_time)
{
	if (*current_time != refresh_time)
	{
		*current_time = refresh_time;
		return 0;
	}
	return 1;
}

#define MAX_INPUT_BUFFER_SIZE 128

int input_check()
{
	char buf[MAX_INPUT_BUFFER_SIZE];
	int bytes_of_stream = 0, readed_chars = 0;

	ioctl(fileno(stdin), FIONREAD, &bytes_of_stream);

	if (bytes_of_stream > 0)
	{
		readed_chars = read(fileno(stdin), buf, bytes_of_stream);

		if (readed_chars > 0)
		{
			for (int i = 0; i < readed_chars; ++i)
			{
				switch (buf[i])
				{
				case 'h':
				{
					active_page = P_HELP;
					wclear(main_page);
					break;
				}
				case 'c':
				{
					active_page = P_CPU_INFO;
					wclear(main_page);
					break;
				}
				case '>':
				{
					if (active_page == P_CPU_INFO && selected_processor_id < data->cpu->processors_num - 1)
					{
						selected_processor_id++;
						break;
					}
					else if (active_page == P_NETWORK_STATS && selected_intf < data->network->interfaces_num - 1)
					{
						selected_intf++;
						break;
					}
					else
						return 0;
				}
				case '<':
				{
					if (active_page == P_CPU_INFO && selected_processor_id > 0)
					{
						selected_processor_id--;
						break;
					}
					else if (active_page == P_NETWORK_STATS && selected_intf > 0)
					{
						selected_intf--;
						break;
					}
					else
						return 0;
				}
				case 'C':
				{
					active_page = P_CPU_LOAD;
					wclear(main_page);
					break;
				}
				case 't':
				{
					prev_page = active_page;
					active_page = P_INPUT_TIME;
					wclear(main_page);
					break;
				}
				case 'l':
				{
					active_page = P_CPU_CORES_LOAD;
					wclear(main_page);
					break;
				}
				case 'm':
				{
					active_page = P_MEMORY;
					wclear(main_page);
					break;
				}
				case 'M':
				{
					active_page = P_MEMORY_LOAD;
					wclear(main_page);
					break;
				}
				case 'n':
				{
					active_page = P_NETWORK_STATS;
					wclear(main_page);
					break;
				}
				case 'r':
				{
					prev_page = active_page;
					active_page = P_REPORT;
					wclear(main_page);
					break;
				}
				case 'q':
				{
					return -1;
				}
				default:
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}

void print_start_page()
{
	PAGE("Menu");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 0, "MySysInfo is a program that collects and displays system data and resources.");
	mvwprintw(main_page, 2, 0, "Users can monitor and analyze processor workload, memory, and network load.");
	mvwprintw(main_page, 3, 0, "It operates in the terminal, providing detailed information about the system.");
	mvwprintw(main_page, 4, 0, "Dynamic graphs and visualization tools are used to present the information.");
	mvwprintw(main_page, 8, 0, "Here are the options:");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 9, 0, " 'c' - CPU Info        	'l' - CPU Cores Load      't' - Set Refresh Time");
	mvwprintw(main_page, 10, 0, " 'C' - CPU Total Load   'U' - Utilisation");
	mvwprintw(main_page, 11, 0, " 'm' - Memory Usage     'V' - Virtual memory");
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
	wnoutrefresh(stdscr);
}

void print_report_page()
{
	PAGE("System Report");

	make_system_report(data);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 0, "*********************************");
	mvwprintw(main_page, 2, 0, "******* REPORT CREATED **********");
	mvwprintw(main_page, 3, 0, "*********************************");
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
	wnoutrefresh(stdscr);
}

void print_help_page()
{
	PAGE("Help");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 0, 1, "Available options:");
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 1, 1,
			  "'h' - Help                       	 | r = Resources OS & Proc");
	mvwprintw(main_page, 2, 1,
			  "'c' - CPU info ('<' - prev | '>' - next) | l = CPU cores load");
	mvwprintw(main_page, 3, 1,
			  "'m' - Memory & Swap                   	| V = Virtual Memory");
	mvwprintw(main_page, 4, 1,
			  "n = Network                           	| N = NFS");
	mvwprintw(main_page, 5, 1,
			  "d = Disk I/O Graphs  D=Stats          	| o = Disks %%Busy Map");
	mvwprintw(main_page, 6, 1,
			  "k = Kernel stats & loadavg            	| j = Filesystem Usage J=reduced");
	mvwprintw(main_page, 7, 1, "M = MHz by thread & CPU");

	mvwprintw(main_page, 8, 1,
			  "t = TopProcess 1=Priority/Nice/State  	| u = TopProc with command line");
	mvwprintw(main_page, 9, 1,
			  "    ReOrder by: 3=CPU 4=RAM 5=I/O    	|     Hit u twice to update");
	mvwprintw(main_page, 10, 1,
			  "g = User Defined Disk Groups          	| G = with -g switches Disk graphs");
	mvwprintw(main_page, 11, 1,
			  "    [start nmon with -g <filename>]   	|     to disk groups only");
	mvwprintw(main_page, 12, 39, "| b = black & white mode");
	mvwprintw(main_page, 13, 1,
			  "Other Controls:                       	|");
	mvwprintw(main_page, 14, 1,
			  "t = Set refresh time    	| 0 = reset peak marks (\">\") to zero");
	mvwprintw(main_page, 15, 1,
			  "- = half   the screen refresh time    	| space refresh screen now");
	mvwprintw(main_page, 16, 1,
			  ". = Display only busy disks & CPU     	| 'q' - Quit");

	wattrset(main_page, COLOR_PAIR(29));
	mvwprintw_clr(main_page, 17, 1, "Refresh interval: %0.1f sec", (double)refresh_time / 10);
	wattrset(main_page, COLOR_PAIR(0));

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

int start_main_ui()
{
	bool is_time_changed = false;

	initscr();
	cbreak();
	move(0, 0);
	refresh();

	int color = has_colors();
	if (color)
	{
		start_color();
		init_pairs(color);
	}

	clear();

	main_page = newpad(MAX_ROWS_COUNT, MAX_COLS_COUNT);

	wbkgd(stdscr, COLOR_PAIR(14));
	wbkgd(main_page, COLOR_PAIR(14));

	fflush(NULL); // think about it

	current_lines = LINES;
	current_cols = COLS;

	init_system_data(&data);

	while (true)
	{
		box(stdscr, 0, 0);
		mvprintw(0, current_cols / 2 - 5, "MySysInfo");
		wnoutrefresh(stdscr);

		switch (active_page)
		{
		case P_DEFAULT:
		{
			print_start_page();
			break;
		}
		case P_HELP:
		{
			print_help_page();
			break;
		}
		case P_CPU_INFO:
		{
			print_cpu_info_page(main_page, data->cpu, selected_processor_id);
			break;
		}
		case P_CPU_LOAD:
		{
			print_cpu_load_graph(main_page, data->cpu, refresh_time, current_cols - GRAPH_RIGHT_BOUNDARY);
			break;
		}
		case P_CPU_CORES_LOAD:
		{
			print_cpu_cores_load(main_page, data->cpu, refresh_time, current_cols);
			break;
		}
		case P_MEMORY:
		{
			print_memory_page(main_page, data->memory);
			break;
		}
		case P_MEMORY_LOAD:
		{
			print_memory_load_graph(main_page, data->memory, refresh_time, current_cols - GRAPH_RIGHT_BOUNDARY);
			break;
		}
		case P_NETWORK_STATS:
		{
			print_network_bandwitdh_graph(main_page, data->network, refresh_time, selected_intf, current_cols - GRAPH_RIGHT_BOUNDARY);
			break;
		}
		case P_REPORT:
		{
			print_report_page();
			active_page = prev_page;
			wclear(main_page);
			break;
		}
		case P_INPUT_TIME:
		{
			refresh_time = input_refresh_time();
			active_page = prev_page;
			is_time_changed = true;
			break;
		}
		default:
			break;
		}
		wmove(stdscr, 0, 0);
		wrefresh(stdscr);
		doupdate();

		int input_value = 0;
		for (int i = 0; i < refresh_time; i++)
		{
			usleep(100000);
			input_value = input_check();
			if (input_value == -1)
			{
				//TODO: free main_page
				free_system_data(data);
				nocbreak();
				endwin();
				return 0;
			}
			else if (input_value == 1 || !check_window_resize(&current_lines, &current_cols)
									  || is_time_changed)
				break;
		}

		is_time_changed = false;
	}
	return 1;
}
