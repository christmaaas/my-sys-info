#include "report.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>

#define MAX_REPORT_NAME_SIZE 100

#define MHz 1000.0
#define KiB 1024.0
#define MiB (KiB * KiB)
#define SEC 10

void make_system_report(system_t* data, const int ref_time)
{
    time_t current_time     = time(NULL);
    struct tm* current_date = localtime(&current_time);

    char report_name[MAX_REPORT_NAME_SIZE];
    sprintf(report_name, "../reports/MySysInfo Report [%02d-%02d-%04d %02d:%02d:%02d].txt",
            current_date->tm_mday, current_date->tm_mon + 1, current_date->tm_year + 1900,
            current_date->tm_hour, current_date->tm_min, current_date->tm_sec);

    FILE* file_ptr = NULL;

    if ((file_ptr = fopen(report_name, "w")) == NULL) 
    {
        perror("Error to open file in \"report.c\" : make_system_report()");
        return;
    }
    fprintf(file_ptr, "======================== MySysInfo System Report ========================\n\n");
    fprintf(file_ptr, "Date & Time: [%02d-%02d-%04d %02d:%02d:%02d]\n\n",
            current_date->tm_mday, current_date->tm_mon + 1, current_date->tm_year + 1900,
            current_date->tm_hour, current_date->tm_min, current_date->tm_sec);

    struct utsname uts;
    uname(&uts);

    fprintf(file_ptr, "User: %s\n", getlogin());
    fprintf(file_ptr, "Hostname: %s\n", uts.nodename);
	fprintf(file_ptr, "Linux: %s\n", uts.version);
	fprintf(file_ptr, "Release: %s\n", uts.release);
	fprintf(file_ptr, "Machine: %s\n", uts.machine);
    fprintf(file_ptr, "Refresh time: %0.1f sec\n\n", (double)ref_time / SEC);

    fprintf(file_ptr, "CPU Information:\n");
    for (uint32_t i = 0; i < data->cpu->processors_num; i++)
    {
        refresh_cpu_clocks(data->cpu, i);

        fprintf(file_ptr, " - Processor ID: %hu\n", data->cpu->compound[i].topology.thread_id + 1);
        fprintf(file_ptr, "   - Physical number: %hu\n", data->cpu->compound[i].topology.socket_id);
        fprintf(file_ptr, "   - Name: %s\n", data->cpu->compound[i].model_name);
        fprintf(file_ptr, "   - Vendor: %s\n", data->cpu->compound[i].vendor_name);
        fprintf(file_ptr, "   - Cores: %hu\n", data->cpu->compound[i].cores_num);
        fprintf(file_ptr, "   - Threads: %hu\n", data->cpu->compound[i].threads_num);
        fprintf(file_ptr, "   - Model number: %u\n", data->cpu->compound[i].model_number);
        fprintf(file_ptr, "   - Family number: %u\n", data->cpu->compound[i].family_number);
        fprintf(file_ptr, "   - Stepping number: %u\n", data->cpu->compound[i].stepping_number);
        fprintf(file_ptr, "   - Cpuid level: %u\n", data->cpu->compound[i].cpuid_level);
        fprintf(file_ptr, "   - Cache allignment: %u\n", data->cpu->compound[i].cache_alignment);
        fprintf(file_ptr, "   - Microcode name: %s\n", data->cpu->compound[i].microcode_name);
        fprintf(file_ptr, "   - Byte order: %s\n",
				            data->cpu->compound[i].byte_oder == LITTLE_ENDIAN_ORDER ? "little endian" : "big endian");
        fprintf(file_ptr, "   - Bogomips: %0.2f\n", data->cpu->compound[i].bogomips);
        fprintf(file_ptr, "   - Core ID: %hu\n", data->cpu->compound[i].topology.core_id);
        fprintf(file_ptr, "   - Frequency:\n");
        fprintf(file_ptr, "     - Max:     %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_max / MHz);
        fprintf(file_ptr, "     - Current: %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_cur / MHz);
        fprintf(file_ptr, "     - Base:    %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_base / MHz);
        fprintf(file_ptr, "     - Min:     %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_min / MHz);
        fprintf(file_ptr, "     - Scaling governor: %s\n", data->cpu->compound[i].frequency.freq_scaling_governor);
        fprintf(file_ptr, "     - Latency: %d\n", data->cpu->compound[i].frequency.transition_latency);
        fprintf(file_ptr, "     - Affected processors: %d\n", data->cpu->compound[i].frequency.affected_cpus);
        fprintf(file_ptr, "   - Cache:\n");
        fprintf(file_ptr, "     - Lvl1 (D) size:      %uKB\n", data->cpu->compound[i].cache.l1_data_size);
        fprintf(file_ptr, "     - Lvl1 (I) size:      %uKB\n", data->cpu->compound[i].cache.l1_inst_size);
        fprintf(file_ptr, "     - Lvl2 size:          %uKB\n", data->cpu->compound[i].cache.l2_size);
        fprintf(file_ptr, "     - Lvl3 size:          %uKB\n\n", data->cpu->compound[i].cache.l3_size);
        fprintf(file_ptr, "     - Lvl1 (D) line size: %uKB\n", data->cpu->compound[i].cache.l1_data_line_size);
        fprintf(file_ptr, "     - Lvl1 (I) line size: %uKB\n", data->cpu->compound[i].cache.l1_inst_line_size);
        fprintf(file_ptr, "     - Lvl2 line size:     %uKB\n", data->cpu->compound[i].cache.l2_line_size);
        fprintf(file_ptr, "     - Lvl3 line size:     %uKB\n\n", data->cpu->compound[i].cache.l3_line_size);
        fprintf(file_ptr, "     - Lvl1 (D) sets:      %u\n", data->cpu->compound[i].cache.l1_data_sets);
        fprintf(file_ptr, "     - Lvl1 (I) sets:      %u\n", data->cpu->compound[i].cache.l1_inst_sets);
        fprintf(file_ptr, "     - Lvl2 sets:          %u\n", data->cpu->compound[i].cache.l2_sets);
        fprintf(file_ptr, "     - Lvl3 sets:          %u\n\n", data->cpu->compound[i].cache.l3_sets);
        fprintf(file_ptr, "     - Lvl1 (D) ways:      %u\n", data->cpu->compound[i].cache.l1_data_ways);
        fprintf(file_ptr, "     - Lvl1 (I) ways:      %u\n", data->cpu->compound[i].cache.l1_inst_ways);
        fprintf(file_ptr, "     - Lvl2 ways:          %u\n", data->cpu->compound[i].cache.l2_ways);
        fprintf(file_ptr, "     - Lvl3 ways:          %u\n", data->cpu->compound[i].cache.l3_ways);

        if (data->cpu->compound[i].cache.levels_num > 3)
	    {
		    fprintf(file_ptr, "     - Lvl4 size: %uKB\n", data->cpu->compound[i].cache.l4_size);
		    fprintf(file_ptr, "     - Lvl4 line size: %uKB\n", data->cpu->compound[i].cache.l4_line_size);
		    fprintf(file_ptr, "     - Lvl4 sets: %u\n", data->cpu->compound[i].cache.l4_sets);
		    fprintf(file_ptr, "     - Lvl4 ways: %u\n", data->cpu->compound[i].cache.l4_ways);
	    }
    }

    calculate_cpu_cores_load(data->cpu);

    fprintf(file_ptr, "\n - Current CPU Average Usage: %0.1f%%\n\n", data->cpu->current_load.avg_load);
    fprintf(file_ptr, " - Current CPU Each Usage:\n");
    for (uint32_t i = 0; i < data->cpu->processors_num; i++)
        fprintf(file_ptr, "   - PROC#%hu: %0.1f%%\n", data->cpu->compound[i].topology.thread_id + 1, 
                                                    data->cpu->current_load.cores_load[i].user 
                                                    + data->cpu->current_load.cores_load[i].wait 
                                                    + data->cpu->current_load.cores_load[i].sys);

    calculate_memory_usage_percentage(data->memory);

    fprintf(file_ptr, "\nMemory Information:\n");
    fprintf(file_ptr, " - Pages:\n");
    fprintf(file_ptr, "   - Anon Pages:  %0.1fMiB\n", data->memory->usage_stats.anon_pages / KiB);
    fprintf(file_ptr, "   - Page Tables: %0.1fMiB\n", data->memory->usage_stats.page_tables / KiB);
    fprintf(file_ptr, " - Activity:\n");
    fprintf(file_ptr, "   - Active:   %0.1fMiB\n", data->memory->usage_stats.active / KiB);
    fprintf(file_ptr, "   - Inactive: %0.1fMiB\n\n", data->memory->usage_stats.inactive / KiB);
    fprintf(file_ptr, " - Shared: %0.1fMiB\n", data->memory->usage_stats.shmem / KiB);
    fprintf(file_ptr, " - Mapped: %0.1fMiB\n\n", data->memory->usage_stats.mapped / KiB);
    fprintf(file_ptr, " - RAM Total:  %0.1fMiB\n", data->memory->usage_stats.total / KiB);
    fprintf(file_ptr, " - Swap Total: %0.1fMiB\n\n", data->memory->usage_stats.swap_total / KiB);
    fprintf(file_ptr, " - RAM Usage:   %0.1fMiB(%3.1lf%%)\n", data->memory->usage_stats.usage / KiB, 
														data->memory->usage_percentage.usage);
    fprintf(file_ptr, " - RAM Buffers: %0.1fMiB(%3.1lf%%)\n", data->memory->usage_stats.buffers / KiB,
														data->memory->usage_percentage.buffers);                                                    
    fprintf(file_ptr, " - RAM Cached:  %0.1fMiB(%3.1lf%%)\n", data->memory->usage_stats.cached / KiB,
														 data->memory->usage_percentage.cached);
    fprintf(file_ptr, " - RAM Free:    %0.1fMiB(%3.1lf%%)\n\n", data->memory->usage_stats.free / KiB,
														 data->memory->usage_percentage.free);
    fprintf(file_ptr, " - Swap Usage:  %0.1fMiB(%3.1lf%%)\n", data->memory->usage_stats.swap_usage / KiB,
														 data->memory->usage_percentage.swap_usage);
    fprintf(file_ptr, " - Swap Free:   %0.1fMiB(%3.1lf%%)\n\n", data->memory->usage_stats.swap_free / KiB,
														 data->memory->usage_percentage.swap_free);

    fprintf(file_ptr, "Network Information:\n");
    for (uint32_t i = 0 ; i < data->network->interfaces_num; i++)
    {
        fprintf(file_ptr, " - Interface %s (%d/%d)\n", data->network->stat[i].interface_name, 
                                                    i + 1, 
                                                    data->network->interfaces_num);
        fprintf(file_ptr, "   - Received:\n");
        fprintf(file_ptr, "     - Current Bandwidth: %0.2f KiB/s\n", data->network->stat[i].r_bandwith.cur / KiB);
        fprintf(file_ptr, "     - Avg Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].r_bandwith.avg / KiB);
        fprintf(file_ptr, "     - Min Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].r_bandwith.min / KiB);
        fprintf(file_ptr, "     - Max Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].r_bandwith.max / KiB);
        fprintf(file_ptr, "     - Total Received:    %0.2f MiB\n", data->network->stat[i].r_bytes / MiB);
        fprintf(file_ptr, "   - Transmitted:\n");
        fprintf(file_ptr, "     - Current Bandwidth: %0.2f KiB/s\n", data->network->stat[i].t_bandwith.cur / KiB);
        fprintf(file_ptr, "     - Avg Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].t_bandwith.avg / KiB);
        fprintf(file_ptr, "     - Min Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].t_bandwith.min / KiB);
        fprintf(file_ptr, "     - Max Bandwidth:     %0.2f KiB/s\n", data->network->stat[i].t_bandwith.max / KiB);
        fprintf(file_ptr, "     - Total Transmitted: %0.2f MiB\n", data->network->stat[i].t_bytes / MiB);
        fprintf(file_ptr, "   - Received packets:    %lu\n", data->network->stat[i].r_packets);
        fprintf(file_ptr, "   - Received errors:     %lu\n", data->network->stat[i].r_errs);
        fprintf(file_ptr, "   - Received drop:       %lu\n", data->network->stat[i].r_drop);
        fprintf(file_ptr, "   - Transmitted packets: %lu\n", data->network->stat[i].t_packets);
        fprintf(file_ptr, "   - Transmitted errors:  %lu\n", data->network->stat[i].t_errs);
        fprintf(file_ptr, "   - Transmitted drop:    %lu\n", data->network->stat[i].t_drop);
    }

    fprintf(file_ptr, "\nPCI Devices Information:\n");
    for (uint32_t i = 0 ; i < data->pci->devices_num; i++)
    {
        fprintf(file_ptr, " - Device %s (%d/%d)\n", data->pci->devices[i].device_location, i + 1, data->pci->devices_num);
        fprintf(file_ptr, "   - Domain:   %04x\n", data->pci->devices[i].domain);
	    fprintf(file_ptr, "   - Bus:      %02x\n", data->pci->devices[i].bus);
	    fprintf(file_ptr, "   - Device:   %02x\n", data->pci->devices[i].device);
	    fprintf(file_ptr, "   - Function: %x\n\n", data->pci->devices[i].function);
        fprintf(file_ptr, "   - Class:     %s\n", data->pci->devices[i].class_name);
        fprintf(file_ptr, "   - Subclass:  %s\n", 
                            data->pci->devices[i].subclass_name ? data->pci->devices[i].subclass_name : "Not Found");
        fprintf(file_ptr, "   - Interface: %s\n\n", 
                            data->pci->devices[i].interface_name ? data->pci->devices[i].interface_name : "Not Found");
        fprintf(file_ptr, "   - Vendor Name: %s\n", data->pci->devices[i].vendor_name);
        fprintf(file_ptr, "   - Vendor ID:   %04x\n\n", data->pci->devices[i].vendor_id);
        fprintf(file_ptr, "   - Device Name: %s\n",
                            data->pci->devices[i].device_name ? data->pci->devices[i].device_name : "Not Found");
        fprintf(file_ptr, "   - Device ID:   %04x\n\n", data->pci->devices[i].device_id);
        fprintf(file_ptr, "   - Driver:   %s\n\n", data->pci->devices[i].driver_name);
        fprintf(file_ptr, "   - Revision: %02x\n", data->pci->devices[i].revision);
    }

    calculate_sensors_stats(data->sensor);

    fprintf(file_ptr, "\nSystem Sensors Statistics (Temperature in Celtius):\n");
    for (uint32_t i = 0 ; i < data->sensor->sensors_num; i++)
    {
        fprintf(file_ptr, " - Sensor (%d/%d)\n", i + 1, data->sensor->sensors_num);
        fprintf(file_ptr, "   - Current temperature: %d\n", data->sensor->stats[i].cur_temp);
        fprintf(file_ptr, "   - Min temperature:     %d\n", data->sensor->stats[i].min_temp);
        fprintf(file_ptr, "   - Max temperature:     %d\n", data->sensor->stats[i].max_temp);
    }                                                                               
                            
    fclose(file_ptr);
}

