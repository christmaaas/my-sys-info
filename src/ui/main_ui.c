#include "main_ui.h"
#include "../logic/sys.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>

int current_lines;
int current_cols;

int selected_processor_id = 0;

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
						selected_processor_id++;

					break;
				}
				case '<':
				{
					if (active_page == P_CPU_INFO && selected_processor_id > 0)
						selected_processor_id--;

					break;
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

#define PAGE(page_name)                     \
	{                                       \
		wattrset(main_page, COLOR_PAIR(0)); \
		mvprintw(0, 7, page_name);          \
		wnoutrefresh(stdscr);               \
	}

#define mvwprintw_clr(win, y, x, ...)      \ 
	{                                      \
		mvwprintw(win, y, x, __VA_ARGS__); \
		wclrtoeol(win);                    \
	}

void print_start_page()
{
	PAGE("Menu");

	wattrset(main_page, COLOR_PAIR(15));
	mvwprintw(main_page, 0, 3, "=====MySysInfo=====");
	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 3, "Utility provides information about the system and its devices");
	mvwprintw(main_page, 3, 3, "Here are the options:");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 4, 3, "  'c' - CPU info         l = CPU Long-term     t = Set refresh time");
	mvwprintw(main_page, 5, 3, "  'C' - CPU load  U = Utilisation       + = Slower screen updates");
	mvwprintw(main_page, 6, 3, "  m = Memory      V = Virtual memory    j = File Systems");
	mvwprintw(main_page, 7, 3, "  d = Disks       n = Network           . = only busy disks/procs");
	mvwprintw(main_page, 8, 3, "  r = Resource    N = NFS               h = more options");
	mvwprintw(main_page, 9, 3, "  k = Kernel      t = Top-processes     q = Quit");
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
	wnoutrefresh(stdscr);
}

void print_help_page()
{
	PAGE("Help");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 0, 1, "Available options:");
	wattrset(main_page, COLOR_PAIR(12));
	mvwprintw(main_page, 1, 1,
			  "'h' - Help                       	 | r = Resources OS & Proc");
	mvwprintw(main_page, 2, 1,
			  "'c' - CPU info ('<' - prev | '>' - next) | l = longer term CPU averages");
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

	wattrset(main_page, COLOR_PAIR(2));
	mvwprintw_clr(main_page, 17, 1, "Refresh interval: %0.1f sec", (double)refresh_time / 10);
	
	mvwprintw(main_page, 19, 1, "Colour:");
	for (int i = 0; i < 13; i++)
	{
		wattrset(main_page, COLOR_PAIR(i));
		mvwprintw(main_page, 20, 8 + i * 5, "#%d#", i);
	}
	wattrset(main_page, COLOR_PAIR(0));

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

void print_cpu_info_page()
{
	cpucompound_t processor = data->cpu->compound[selected_processor_id];

	PAGE("CPU");

	wattrset(main_page, COLOR_PAIR(17));
	mvwprintw_clr(main_page, 0, 1, "Processor ID: %d", selected_processor_id);

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 1, 1, "Name: %s", processor.model_name);
	mvwprintw_clr(main_page, 2, 1, "Cores: %u", processor.cores_num);
	mvwprintw_clr(main_page, 3, 1, "Threads: %u", processor.threads_num);
	mvwprintw_clr(main_page, 4, 1, "Model number: %u", processor.model_number);
	mvwprintw_clr(main_page, 5, 1, "Family number: %u", processor.family_number);
	mvwprintw_clr(main_page, 6, 1, "Stepping number: %u", processor.stepping_number);
	mvwprintw_clr(main_page, 7, 1, "Cpuid level: %u", processor.cpuid_level);
	mvwprintw_clr(main_page, 8, 1, "Clflush size: %u", processor.clflush_size);
	mvwprintw_clr(main_page, 9, 1, "Cache allignment: %u", processor.cache_alignment);
	mvwprintw_clr(main_page, 10, 1, "Physical number: %u", processor.phys_cpus_num);
	mvwprintw_clr(main_page, 11, 1, "Microcode name: %s", processor.microcode_name);
	mvwprintw_clr(main_page, 12, 1, "Byte order: %s",
				  processor.byte_oder == LITTLE_ENDIAN_ORDER ? "little endian" : "big endian");
	mvwprintw_clr(main_page, 13, 1, "Bogomips: %0.2f", processor.bogomips);
	mvwprintw_clr(main_page, 14, 1, "Core ID: %d", processor.topology.core_id);

	wattrset(main_page, COLOR_PAIR(16));
	mvwprintw_clr(main_page, 16, 1, "Frequency:");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 17, 1, "Max: %0.2fMHz", (double)processor.frequency.freq_max / 1000);
	mvwprintw_clr(main_page, 18, 1, "Current: %0.2fMHz", (double)processor.frequency.freq_cur / 1000);
	mvwprintw_clr(main_page, 17, 20, " | Latency: %d", processor.frequency.transition_latency);
	mvwprintw_clr(main_page, 18, 20, " | Affected processors: %d", processor.frequency.affected_cpus);
	mvwprintw_clr(main_page, 19, 1, "Base: %0.2fMHz", (double)processor.frequency.freq_base / 1000);
	mvwprintw_clr(main_page, 20, 1, "Min: %0.2fMHz", (double)processor.frequency.freq_min / 1000);
	mvwprintw_clr(main_page, 21, 1, "Scaling governor: %s", processor.frequency.freq_scaling_governor);

	wattrset(main_page, COLOR_PAIR(15));
	mvwprintw_clr(main_page, 0, 50, "Cache:");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 1, 50, "Level 1 (D) size: %uKB", processor.cache.l1_data_size);
	mvwprintw_clr(main_page, 2, 50, "Level 1 (I) size: %uKB", processor.cache.l1_inst_size);
	mvwprintw_clr(main_page, 3, 50, "Level 2 size: %uKB", processor.cache.l2_size);
	mvwprintw_clr(main_page, 4, 50, "Level 3 size: %uKB", processor.cache.l3_size);

	mvwprintw_clr(main_page, 6, 50, "Level 1 (D) line size: %uKB", processor.cache.l1_data_line_size);
	mvwprintw_clr(main_page, 7, 50, "Level 1 (I) line size: %uKB", processor.cache.l1_inst_line_size);
	mvwprintw_clr(main_page, 8, 50, "Level 2 line size: %uKB", processor.cache.l2_line_size);
	mvwprintw_clr(main_page, 9, 50, "Level 3 line size: %uKB", processor.cache.l3_line_size);

	mvwprintw_clr(main_page, 11, 50, "Level 1 (D) sets: %u", processor.cache.l1_data_sets);
	mvwprintw_clr(main_page, 12, 50, "Level 1 (I) sets: %u", processor.cache.l1_inst_sets);
	mvwprintw_clr(main_page, 13, 50, "Level 2 sets: %u", processor.cache.l2_sets);
	mvwprintw_clr(main_page, 14, 50, "Level 3 sets: %u", processor.cache.l3_sets);

	mvwprintw_clr(main_page, 16, 50, "Level 1 (D) ways: %u", processor.cache.l1_data_ways);
	mvwprintw_clr(main_page, 17, 50, "Level 1 (I) ways: %u", processor.cache.l1_inst_ways);
	mvwprintw_clr(main_page, 18, 50, "Level 2 ways: %u", processor.cache.l2_ways);
	mvwprintw_clr(main_page, 19, 50, "Level 3 ways: %u", processor.cache.l3_ways);

	if (processor.cache.levels_num > 3)
	{
		mvwprintw_clr(main_page, 21, 50, "Level 4 size: %u", processor.cache.l4_size);
		mvwprintw_clr(main_page, 22, 50, "Level 4 line size: %u", processor.cache.l4_line_size);
		mvwprintw_clr(main_page, 23, 50, "Level 4 sets: %u", processor.cache.l4_sets);
		mvwprintw_clr(main_page, 24, 50, "Level 4 ways: %u", processor.cache.l4_ways);
	}

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define MAX_CPU_GRAPH_HEIGHT	 20
#define GRAPH_POINT_OFFSET 	 	 6
#define GRAPH_DELIM_LINE_OFFSET  4

void draw_cpu_load_graph()
{
	PAGE("CPU Total Load");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 0, "100%%");
	mvwprintw(main_page, 6, 1, "75%%");
	mvwprintw(main_page, 11, 1, "50%%");
	mvwprintw(main_page, 16, 1, "25%%");
	mvwprintw(main_page, 20, 1, "<5%%");

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_CPU_GRAPH_HEIGHT; y++) 
		{
			if(y == 1 || y == 6 || y == 11 || y == 16)
			{
				wattrset(main_page, COLOR_PAIR(15));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((data->cpu->load_history[x].user 
				+ data->cpu->load_history[x].sys 
				+ data->cpu->load_history[x].wait) / 100 * MAX_CPU_GRAPH_HEIGHT > y + 0.5)
			{
				wattrset(main_page, COLOR_PAIR(9));
				mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(0));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(5));
				mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(15));
		mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

int main_window()
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

	fflush(NULL); // mb nuzhno a mb net

	current_lines = LINES;
	current_cols = COLS;

	init_system_data(&data);

	while (true)
	{
		box(stdscr, 0, 0);
		mvprintw(0, COLS / 2.3, "MySysInfo");
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
			print_cpu_info_page();
			refresh_cpu_clocks(data->cpu, selected_processor_id);
			break;
		}
		case P_CPU_LOAD:
		{
			calculate_current_load(data->cpu, current_cols - 8); // -8 cause the graph itself starts with indent of 6
			draw_cpu_load_graph();
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
