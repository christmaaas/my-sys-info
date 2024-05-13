#include "../logic/info/sys.h"
#include "../logic/report/report.h"
#include "main_ui.h"
#include "cpu_ui.h"
#include "mem_ui.h"
#include "net_ui.h"
#include "pci_ui.h"
#include "sensors_ui.h"
#include "time_ui.h"
#include "menu_ui.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#define __USE_MISC
#include <unistd.h>
#include <stdio.h>

extern int fileno(FILE *stream);

#define WAIT_TIME_VALUE   100000 // 0.1 of second (usleep arg is a microseconds)
#define INPUT_BUFFER_SIZE 128

typedef enum active_page
{
    P_HELP           = 0,
    P_CPU_INFO       = 1,
    P_CPU_LOAD       = 2,
    P_INPUT_TIME     = 3,
    P_CPU_CORES_LOAD = 4,
    P_MEMORY         = 5,
    P_MEMORY_LOAD    = 6,
    P_NETWORK_STATS  = 7,
    P_REPORT         = 8,
    P_PCI_INFO       = 9,
    P_SENSORS        = 10,
	P_MENU           = 11
} page_t;

typedef enum control_keys
{
    KEY_P_MENU		= 'm',
	KEY_LEFT_ARROW  = '<',
	KEY_RIGHT_ARROW = '>',
	KEY_QUIT		= 'q'
} key_t;

int current_lines;
int current_cols;
int active_page = P_HELP;
int prev_page;
int refresh_time = SEC; // default value in milliseconds

uint32_t proc_id    = 0; // selected processor id
uint32_t intf_id    = 0; // selected network interface id
uint32_t pci_dev_id = 0; // selected pci-device id

WINDOW* main_page;
system_t* data;

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

int control_handle()
{
	char input_buf[INPUT_BUFFER_SIZE];
	int bytes_of_stream = 0, readed_chars = 0;

	ioctl(fileno(stdin), FIONREAD, &bytes_of_stream);

	if (bytes_of_stream > 0)
	{
		readed_chars = read(fileno(stdin), input_buf, bytes_of_stream);

		if (readed_chars > 0)
		{
			for (int i = 0; i < readed_chars; ++i)
			{
				switch (input_buf[i])
				{
				case KEY_RIGHT_ARROW:
				{
					if (active_page == P_CPU_INFO && proc_id < data->cpu->processors_num - 1)
					{
						proc_id++;
						break;
					}
					else if (active_page == P_NETWORK_STATS && intf_id < data->network->interfaces_num - 1)
					{
						intf_id++;
						break;
					}
					else if (active_page == P_PCI_INFO && pci_dev_id < data->pci->devices_num - 1)
					{
						pci_dev_id++;
						break;
					}
					else
						return 0;
				}
				case KEY_LEFT_ARROW:
				{
					if (active_page == P_CPU_INFO && proc_id > 0)
					{
						proc_id--;
						break;
					}
					else if (active_page == P_NETWORK_STATS && intf_id > 0)
					{
						intf_id--;
						break;
					}
					else if (active_page == P_PCI_INFO && pci_dev_id > 0)
					{
						pci_dev_id--;
						break;
					}
					else
						return 0;
				}
				case KEY_P_MENU:
				{
					prev_page = active_page;
					active_page = P_MENU;
					break;
				}
				case KEY_QUIT:
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

void print_report_page()
{
	wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
	mvprintw(0, PAGE_TITLE_OFFSET, "System Report");
	wnoutrefresh(stdscr);

	make_system_report(data, refresh_time);

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_BLUE));
	mvwprintw(main_page, 1, 0, "*********************************");
	mvwprintw(main_page, 2, 0, "********* REPORT CREATED ********");
	mvwprintw(main_page, 3, 0, "*********************************");
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
	wnoutrefresh(stdscr);
}

void print_help_page()
{
	wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
	mvprintw(0, PAGE_TITLE_OFFSET, "Help");
	wnoutrefresh(stdscr);

	struct utsname uts;
	struct tm*	   tim;
	time_t  	   timer;

	uname(&uts);
	timer = time(NULL);	
	tim = localtime(&timer);	

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 1, 0, "Hostname: %s", uts.nodename);
	mvwprintw(main_page, 2, 0, "Linux: %s", uts.version);
	mvwprintw(main_page, 3, 0, "Release: %s", uts.release);
	mvwprintw(main_page, 4, 0, "Machine: %s", uts.machine);
	mvwprintw(main_page, 5, 0, "Local time: %02d:%02d:%02d", tim->tm_hour, tim->tm_min, tim->tm_sec);

	wattrset(main_page, COLOR_PAIR(PAIR_MAGENDA_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 6, 0, "Refresh time: %0.1f sec", (double)refresh_time / SEC);
	wattroff(main_page, A_BOLD);
	
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw(main_page, 8, 0, "Available options:");
	mvwprintw(main_page, 9, 0, "'m' - Selection Menu");
	mvwprintw(main_page, 10, 0, " - 1. Help");
	mvwprintw(main_page, 11, 0, " - 2. CPU Info ('<' - prev | '>' - next)");
	mvwprintw(main_page, 12, 0, " - 3. CPU Total Load");
	mvwprintw(main_page, 13, 0, " - 4. Set Refresh Time");
	mvwprintw(main_page, 14, 0, " - 5. CPU Each Load");
	mvwprintw(main_page, 15, 0, " - 6. Memory Info");
	mvwprintw(main_page, 16, 0, " - 7. Memory & Swap Load");
	mvwprintw(main_page, 17, 0, " - 8. Network Stats ('<' - prev | '>' - next)");
	mvwprintw(main_page, 18, 0, " - 9. Generate Report");
	mvwprintw(main_page, 19, 0, " - 10.PCI Devices Info ('<' - prev | '>' - next)");
	mvwprintw(main_page, 20, 0, " - 11.Sensors Info");
	mvwprintw(main_page, 21, 0, "'q' - Quit");
	wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

int start_main_ui()
{
	bool is_time_changed = false; // time changing flag 
	bool is_menu_called  = false; // menu calling flag

	initscr();
	cbreak();
	move(0, 0);
	refresh();

	start_color();
	
	init_pair((short)PAIR_DEFAULT, (short)COLOR_WHITE, (short)COLOR_BLACK);
	init_pair((short)PAIR_GREEN_BLACK, (short)COLOR_GREEN, (short)COLOR_BLACK);
	init_pair((short)PAIR_BLUE_BLACK, (short)COLOR_BLUE, (short)COLOR_BLACK);
	init_pair((short)PAIR_MAGENDA_BLACK, (short)COLOR_MAGENTA, (short)COLOR_BLACK);
	init_pair((short)PAIR_BLACK_RED, (short)COLOR_BLACK, (short)COLOR_RED);
	init_pair((short)PAIR_BLACK_GREEN, (short)COLOR_BLACK, (short)COLOR_GREEN);
	init_pair((short)PAIR_BLACK_YELLOW, (short)COLOR_BLACK, (short)COLOR_YELLOW);
	init_pair((short)PAIR_BLACK_CYAN, (short)COLOR_BLACK, (short)COLOR_CYAN);
	init_pair((short)PAIR_BLACK_WHITE, (short)COLOR_BLACK, (short)COLOR_WHITE);
	init_pair((short)PAIR_BLUE_WHITE, (short)COLOR_BLUE, (short)COLOR_WHITE);
	init_pair((short)PAIR_RED_WHITE, (short)COLOR_RED, (short)COLOR_WHITE);
	init_pair((short)PAIR_GREEN_WHITE, (short)COLOR_GREEN, (short)COLOR_WHITE);
	init_pair((short)PAIR_YELLOW_WHITE, (short)COLOR_YELLOW, (short)COLOR_WHITE);
	init_pair((short)PAIR_RED_GREEN, (short)COLOR_RED, (short)COLOR_GREEN);
	init_pair((short)PAIR_MAGENDA_WHITE, (short)COLOR_MAGENTA, (short)COLOR_WHITE);
	init_pair((short)PAIR_MAGENDA_MAGENDA, (short)COLOR_MAGENTA, (short)COLOR_MAGENTA);
	init_pair((short)PAIR_YELLOW_YELLOW, (short)COLOR_YELLOW, (short)COLOR_YELLOW);
	init_pair((short)PAIR_GREEN_GREEN, (short)COLOR_GREEN, (short)COLOR_GREEN);
	init_pair((short)PAIR_BLUE_BLUE, (short)COLOR_BLUE, (short)COLOR_BLUE);
	init_pair((short)PAIR_WHITE_BLUE, (short)COLOR_WHITE, (short)COLOR_BLUE);
	init_pair((short)PAIR_CYAN_BLUE, (short)COLOR_CYAN, (short)COLOR_BLUE);
	init_pair((short)PAIR_GREEN_BLUE, (short)COLOR_GREEN, (short)COLOR_BLUE);
	init_pair((short)PAIR_RED_BLUE, (short)COLOR_RED, (short)COLOR_BLUE);
	init_pair((short)PAIR_YELLOW_BLUE, (short)COLOR_YELLOW, (short)COLOR_BLUE);
	init_pair((short)PAIR_BLUE_YELLOW, (short)COLOR_BLUE, (short)COLOR_YELLOW);
	init_pair((short)PAIR_RED_RED, (short)COLOR_RED, (short)COLOR_RED);
	init_pair((short)PAIR_CYAN_CYAN, (short)COLOR_CYAN, (short)COLOR_CYAN);
	init_pair((short)PAIR_WHITE_RED, (short)COLOR_WHITE, (short)COLOR_RED);
	init_pair((short)PAIR_WHITE_CYAN, (short)COLOR_WHITE, (short)COLOR_CYAN);

	clear();

	main_page = newpad(MAX_ROWS_COUNT, MAX_COLS_COUNT);

	// background color
	wbkgd(stdscr, COLOR_PAIR(PAIR_BLUE_WHITE));
	wbkgd(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));

	fflush(NULL); 

	current_lines = LINES;
	current_cols = COLS;

	// initialize system processed data
	init_system_data(&data);

	while (true)
	{
		box(stdscr, 0, 0);
		wnoutrefresh(stdscr);

		switch (active_page)
		{
		case P_HELP:
		{
			print_help_page();
			break;
		}
		case P_CPU_INFO:
		{
			print_cpu_info_page(main_page, data->cpu, proc_id);
			break;
		}
		case P_CPU_LOAD:
		{
			print_cpu_load_graph(main_page, 
								data->cpu, 
								refresh_time, 
								current_cols - GRAPH_RIGHT_BOUNDARY);
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
			print_memory_load_graph(main_page, 
								data->memory, 
								refresh_time, 
								current_cols - GRAPH_RIGHT_BOUNDARY);
			break;
		}
		case P_NETWORK_STATS:
		{
			print_network_bandwitdh_graph(main_page, 
										data->network, 
										refresh_time, 
										intf_id, 
										current_cols - GRAPH_RIGHT_BOUNDARY);
			break;
		}
		case P_PCI_INFO:
		{
			print_pci_devices_page(main_page, data->pci, pci_dev_id);
			break;
		}
		case P_SENSORS:
		{
			print_sensors_page(main_page, data->sensor, refresh_time, current_cols);
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
		case P_MENU:
		{
			active_page = select_page_menu();
			is_menu_called = true;
			break;
		}
		default:
			break;
		}

		// move course to the beginning each time
		wmove(stdscr, 0, 0); 

		wrefresh(stdscr);

		doupdate();

		int contol_key_value = 0;
		for (int i = 0; i < refresh_time; i++)
		{
			// wait for user input
			usleep(WAIT_TIME_VALUE);

			contol_key_value = control_handle();
			
			if (contol_key_value == -1)
			{
				free_system_data(data);

				nocbreak();

				endwin();
				return 0;
			}
			else if (contol_key_value || !check_window_resize(&current_lines, &current_cols)
									  || is_time_changed
									  || is_menu_called)
			{
				wclear(main_page);
				break;
			}
		}

		// reset flags
		is_time_changed = false;
		is_menu_called  = false;
	}
	return 1;
}
