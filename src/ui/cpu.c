#include "cpu.h"

#include <stdlib.h>

#define MHz 1000.0

void print_cpu_info_page(WINDOW* main_page, cpu_t* cpu, const int proc_id)
{
	PAGE_TITLE("CPU Info");

	refresh_cpu_clocks(cpu, proc_id);

	cpucompound_t processor = cpu->compound[proc_id];

	wattrset(main_page, COLOR_PAIR(PAIR_YELLOW_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 0, 1, "Processor ID:");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 0, 14, "%hu", processor.topology.thread_id + 1);

	wattrset(main_page, COLOR_PAIR(PAIR_CYAN_BLUE));
	mvwprintw_clr(main_page, 1, 1, "Physical number: %hu", processor.topology.socket_id);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 2, 1, "Name: %s", processor.model_name);
	mvwprintw_clr(main_page, 3, 1, "Vendor: %s", processor.vendor_name);
	mvwprintw_clr(main_page, 4, 1, "Cores: %hu", processor.cores_num);
	mvwprintw_clr(main_page, 5, 1, "Threads: %hu", processor.threads_num);
	mvwprintw_clr(main_page, 6, 1, "Model number: %u", processor.model_number);
	mvwprintw_clr(main_page, 7, 1, "Family number: %u", processor.family_number);
	mvwprintw_clr(main_page, 8, 1, "Stepping number: %u", processor.stepping_number);
	mvwprintw_clr(main_page, 9, 1, "Cpuid level: %u", processor.cpuid_level);
	mvwprintw_clr(main_page, 10, 1, "Cache allignment: %u", processor.cache_alignment);
	mvwprintw_clr(main_page, 11, 1, "Microcode name: %s", processor.microcode_name);
	mvwprintw_clr(main_page, 12, 1, "Byte order: %s",
				  processor.byte_oder == LITTLE_ENDIAN_ORDER ? "little endian" : "big endian");
	mvwprintw_clr(main_page, 13, 1, "Bogomips: %0.2f", processor.bogomips);
	mvwprintw_clr(main_page, 14, 1, "Core ID: %hu", processor.topology.core_id);

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 16, 1, "Frequency:");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 17, 1, "Max: %0.2fMHz", (double)processor.frequency.freq_max / MHz);
	mvwprintw_clr(main_page, 18, 1, "Current: %0.2fMHz", (double)processor.frequency.freq_cur / MHz);
	mvwprintw_clr(main_page, 17, 20, " | Latency: %d", processor.frequency.transition_latency);
	mvwprintw_clr(main_page, 18, 20, " | Affected processors: %d", processor.frequency.affected_cpus);
	mvwprintw_clr(main_page, 19, 1, "Base: %0.2fMHz", (double)processor.frequency.freq_base / MHz);
	mvwprintw_clr(main_page, 20, 1, "Min: %0.2fMHz", (double)processor.frequency.freq_min / MHz);
	mvwprintw_clr(main_page, 21, 1, "Scaling governor: %s", processor.frequency.freq_scaling_governor);

	wattrset(main_page, COLOR_PAIR(PAIR_RED_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 0, 50, "Cache:");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw_clr(main_page, 1, 50, "Lvl1 (D) size: %uKB", processor.cache.l1_data_size);
	mvwprintw_clr(main_page, 2, 50, "Lvl1 (I) size: %uKB", processor.cache.l1_inst_size);
	mvwprintw_clr(main_page, 3, 50, "Lvl2 size: %uKB", processor.cache.l2_size);
	mvwprintw_clr(main_page, 4, 50, "Lvl3 size: %uKB", processor.cache.l3_size);

	mvwprintw_clr(main_page, 6, 50, "Lvl1 (D) line size: %uKB", processor.cache.l1_data_line_size);
	mvwprintw_clr(main_page, 7, 50, "Lvl1 (I) line size: %uKB", processor.cache.l1_inst_line_size);
	mvwprintw_clr(main_page, 8, 50, "Lvl2 line size: %uKB", processor.cache.l2_line_size);
	mvwprintw_clr(main_page, 9, 50, "Lvl3 line size: %uKB", processor.cache.l3_line_size);

	mvwprintw_clr(main_page, 11, 50, "Lvl1 (D) sets: %u", processor.cache.l1_data_sets);
	mvwprintw_clr(main_page, 12, 50, "Lvl1 (I) sets: %u", processor.cache.l1_inst_sets);
	mvwprintw_clr(main_page, 13, 50, "Lvl2 sets: %u", processor.cache.l2_sets);
	mvwprintw_clr(main_page, 14, 50, "Lvl3 sets: %u", processor.cache.l3_sets);

	mvwprintw_clr(main_page, 16, 50, "Lvl1 (D) ways: %u", processor.cache.l1_data_ways);
	mvwprintw_clr(main_page, 17, 50, "Lvl1 (I) ways: %u", processor.cache.l1_inst_ways);
	mvwprintw_clr(main_page, 18, 50, "Lvl2 ways: %u", processor.cache.l2_ways);
	mvwprintw_clr(main_page, 19, 50, "Lvl3 ways: %u", processor.cache.l3_ways);

	if (processor.cache.levels_num > 3)
	{
		mvwprintw_clr(main_page, 21, 50, "Lvl4 size: %uKB", processor.cache.l4_size);
		mvwprintw_clr(main_page, 22, 50, "Lvl4 line size: %uKB", processor.cache.l4_line_size);
		mvwprintw_clr(main_page, 23, 50, "Lvl4 sets: %u", processor.cache.l4_sets);
		mvwprintw_clr(main_page, 24, 50, "Lvl4 ways: %u", processor.cache.l4_ways);
	}

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define MAX_CPU_GRAPH_HEIGHT 20

void print_cpu_load_graph(WINDOW* main_page, cpu_t* cpu, const int time, const int graph_width)
{
	PAGE_TITLE("CPU Total Usage");

	calculate_total_cpu_load(cpu, graph_width);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, 1, 0, "100%%");
	mvwprintw(main_page, 6, 1, "75%%");
	mvwprintw(main_page, 11, 1, "50%%");
	mvwprintw(main_page, 16, 1, "25%%");
	mvwprintw(main_page, 21, 2, "0%%");

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw_clr(main_page, 0, 0, "CPU total usage/time graph | time: %0.1f sec", (double)time / SEC);
	wattron(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_GREEN_GREEN));
	mvwprintw(main_page, 0, 45, " ");

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 0, 46, " - current usage");
	wattroff(main_page, A_BOLD);

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_CPU_GRAPH_HEIGHT; y++) 
		{
			if (y == 1 || y == 6 || y == 11 || y == 16)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((cpu->current_load.load_history[x].user 
				+ cpu->current_load.load_history[x].sys 
				+ cpu->current_load.load_history[x].wait) / 100.0 
				* MAX_CPU_GRAPH_HEIGHT > y + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_BLACK_GREEN));
				mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(PAIR_MAGENDA_BLACK));
				mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT - y, x + GRAPH_POINT_OFFSET, ACS_PLUS);
			}
		}
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define GRAPH_BOUNDARY_OFFSET 	15
#define CORES_LOAD_GRAPH_OFFSET 11
#define INITIAL_GRAPH_OFFSET  	10

void print_cpu_cores_load(WINDOW* main_page, cpu_t* cpu, const int time, const int cols)
{
	PAGE_TITLE("CPU Each Usage");

	calculate_cpu_cores_load(cpu);

	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, 0, 0, "CPU each usage/time diagram | time: %0.1f sec", (double)time / SEC);
	wattroff(main_page, A_BOLD);

	for (uint32_t i = 0; i < cpu->processors_num; i++)
	{
		wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
		mvwprintw(main_page, i + 2, 0, "PROC #%hu", cpu->compound[i].topology.thread_id + 1);
		mvwprintw(main_page, i + 2, INITIAL_GRAPH_OFFSET, "[");
		mvwprintw(main_page, i + 2, cols - GRAPH_BOUNDARY_OFFSET + 1, "]");

		double core_load = cpu->current_load.cores_load[i].user 
							+ cpu->current_load.cores_load[i].wait 
							+ cpu->current_load.cores_load[i].sys;

		for (int j = 0; j < cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; j++)
		{
			if (core_load / 100.0 
				* (cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET) > j + GRAPH_THRESHOLD_VALUE)
			{
				wattrset(main_page, COLOR_PAIR(PAIR_RED_GREEN));
				mvwaddch(main_page, i + 2, j + CORES_LOAD_GRAPH_OFFSET, '|');
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
				mvwaddch(main_page, i + 2, j + CORES_LOAD_GRAPH_OFFSET, '.');
			}
		}
		wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
		mvwprintw_clr(main_page, i + 2, cols - GRAPH_BOUNDARY_OFFSET + 2, "%0.1f%%", core_load);
	}
	
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	wattron(main_page, A_BOLD);
	mvwprintw(main_page, cpu->processors_num + 3, 0, "AVERAGE");
	wattroff(main_page, A_BOLD);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	mvwprintw(main_page, cpu->processors_num + 3, INITIAL_GRAPH_OFFSET, "[");
	mvwprintw(main_page, cpu->processors_num + 3, cols - GRAPH_BOUNDARY_OFFSET + 1, "]");

	for (int i = 0; i < cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; i++)
	{
		if (cpu->current_load.avg_load / 100.0 
			* (cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET) > i + GRAPH_THRESHOLD_VALUE)
		{
			wattrset(main_page, COLOR_PAIR(PAIR_RED_GREEN));
			mvwaddch(main_page, cpu->processors_num + 3, i + CORES_LOAD_GRAPH_OFFSET, '|'); 
		}
		else
		{
			wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT));
			mvwaddch(main_page, cpu->processors_num + 3, i + CORES_LOAD_GRAPH_OFFSET, '.');
		}
	}
	wattrset(main_page, COLOR_PAIR(PAIR_BLACK_WHITE));
	mvwprintw_clr(main_page, cpu->processors_num + 3, 
					cols - GRAPH_BOUNDARY_OFFSET + 2, "%0.1f%%", cpu->current_load.avg_load);

	wattrset(main_page, COLOR_PAIR(PAIR_BLUE_WHITE));
	for (int i = 0; i < cols; i++)
	{
		mvwaddch(main_page, 1, i, '=');
		mvwaddch(main_page, cpu->processors_num + 2, i, '=');
		mvwaddch(main_page, cpu->processors_num + 4, i, '=');
	}

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}