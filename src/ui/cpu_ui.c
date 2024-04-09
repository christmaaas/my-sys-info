#include "cpu_ui.h"

#include <stdlib.h>

void print_cpu_info_page(WINDOW* main_page, system_t* data, int selected_processor_id)
{
	cpucompound_t processor = data->cpu->compound[selected_processor_id];

	PAGE("CPU Info");

	wattrset(main_page, COLOR_PAIR(29));
	mvwprintw(main_page, 0, 1, "Processor ID:");
	wattrset(main_page, COLOR_PAIR(30));
	mvwprintw_clr(main_page, 0, 14, "%d", selected_processor_id)

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

	wattrset(main_page, COLOR_PAIR(27));
	mvwprintw_clr(main_page, 16, 1, "Frequency:");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw_clr(main_page, 17, 1, "Max: %0.2fMHz", (double)processor.frequency.freq_max / 1000);
	mvwprintw_clr(main_page, 18, 1, "Current: %0.2fMHz", (double)processor.frequency.freq_cur / 1000);
	mvwprintw_clr(main_page, 17, 20, " | Latency: %d", processor.frequency.transition_latency);
	mvwprintw_clr(main_page, 18, 20, " | Affected processors: %d", processor.frequency.affected_cpus);
	mvwprintw_clr(main_page, 19, 1, "Base: %0.2fMHz", (double)processor.frequency.freq_base / 1000);
	mvwprintw_clr(main_page, 20, 1, "Min: %0.2fMHz", (double)processor.frequency.freq_min / 1000);
	mvwprintw_clr(main_page, 21, 1, "Scaling governor: %s", processor.frequency.freq_scaling_governor);

	wattrset(main_page, COLOR_PAIR(28));
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

void print_cpu_load_graph(WINDOW* main_page, system_t* data, int refresh_time)
{
	PAGE("CPU Total Load");

	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, 1, 0, "100%%");
	mvwprintw(main_page, 6, 1, "75%%");
	mvwprintw(main_page, 11, 1, "50%%");
	mvwprintw(main_page, 16, 1, "25%%");
	mvwprintw(main_page, 21, 1, "<5%%");

	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw_clr(main_page, 0, 0, "CPU AVGload/time graph | time: %0.1f sec", (double)refresh_time / 10);
	wattrset(main_page, COLOR_PAIR(22));
	mvwprintw(main_page, 0, 45, " ");
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 0, 46, " - current load");

	for (int x = 0; x < MAX_COLS_COUNT; x++) 
	{
	    for (int y = 0; y < MAX_CPU_GRAPH_HEIGHT; y++) 
		{
			if (y == 1 || y == 6 || y == 11 || y == 16)
			{
				wattrset(main_page, COLOR_PAIR(14));
				mvwaddch(main_page, y, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
			}
			if ((data->cpu->current_load.load_history[x].user 
				+ data->cpu->current_load.load_history[x].sys 
				+ data->cpu->current_load.load_history[x].wait) / 100 * MAX_CPU_GRAPH_HEIGHT > y + 0.5)
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
		wattrset(main_page, COLOR_PAIR(14));
		mvwaddch(main_page, MAX_CPU_GRAPH_HEIGHT + 1, x + GRAPH_DELIM_LINE_OFFSET, ACS_HLINE);
	}
	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);
}

#define GRAPH_BOUNDARY_OFFSET 	 15
#define CORES_LOAD_GRAPH_OFFSET  11
#define INITIAL_GRAPH_OFFSET  	 10

void print_cpu_cores_load(WINDOW* main_page, system_t* data, int refresh_time, int current_cols)
{
	PAGE("CPU Cores Load");

	loadpercent_t* cores_load = calculate_cpu_cores_load(data->cpu);

	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, 0, 0, "CPUs load/time graph | time: %0.1f sec", (double)refresh_time / 10);

	for (uint32_t i = 0; i < data->cpu->processors_num; i++)
	{
		wattrset(main_page, COLOR_PAIR(14));
		mvwprintw(main_page, i + 1, 0, "CORE #%d", i + 1);
		mvwprintw(main_page, i + 1, INITIAL_GRAPH_OFFSET, "[");
		mvwprintw(main_page, i + 1, current_cols - GRAPH_BOUNDARY_OFFSET + 1, "]");

		double core_load = cores_load[i].user + cores_load[i].wait + cores_load[i].sys;
		for (int j = 0; j < current_cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; j++)
		{
			if (core_load / 100 * (current_cols - GRAPH_BOUNDARY_OFFSET) > j + 0.5)
			{
				wattrset(main_page, COLOR_PAIR(18));
				mvwaddch(main_page, i + 1, j + CORES_LOAD_GRAPH_OFFSET, '|');
			}
			else
			{
				wattrset(main_page, COLOR_PAIR(0));
				mvwaddch(main_page, i + 1, j + CORES_LOAD_GRAPH_OFFSET, '.');
			}
		}
		wattrset(main_page, COLOR_PAIR(13));
		mvwprintw_clr(main_page, i + 1, current_cols - GRAPH_BOUNDARY_OFFSET + 2, "%0.2f%%", core_load);
	}
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw(main_page, data->cpu->processors_num + 2, 0, "AVG load");
	wattrset(main_page, COLOR_PAIR(14));
	mvwprintw(main_page, data->cpu->processors_num + 2, INITIAL_GRAPH_OFFSET, "[");
	mvwprintw(main_page, data->cpu->processors_num + 2, current_cols - GRAPH_BOUNDARY_OFFSET + 1, "]");

	double avg_cores_load = get_avg_cores_load(data->cpu, cores_load);
	for (int i = 0; i < current_cols - GRAPH_BOUNDARY_OFFSET - INITIAL_GRAPH_OFFSET; i++)
	{
		if (avg_cores_load / 100 * (current_cols - GRAPH_BOUNDARY_OFFSET) > i + 0.5)
		{
			wattrset(main_page, COLOR_PAIR(18));
			mvwaddch(main_page, data->cpu->processors_num + 2, i + CORES_LOAD_GRAPH_OFFSET, '|'); 
		}
		else
		{
			wattrset(main_page, COLOR_PAIR(0));
			mvwaddch(main_page, data->cpu->processors_num + 2, i + CORES_LOAD_GRAPH_OFFSET, '.');
		}
	}
	wattrset(main_page, COLOR_PAIR(13));
	mvwprintw_clr(main_page, data->cpu->processors_num + 2, 
					current_cols - GRAPH_BOUNDARY_OFFSET + 2, "%0.2f%%", avg_cores_load);

	pnoutrefresh(main_page, 0, 0, 1, 1, LINES - 2, COLS - 2);

	free(cores_load);
}