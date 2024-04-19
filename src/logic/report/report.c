#include "report.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_REPORT_NAME_SIZE 100

#define MHZ 1000
#define KB  1024.0
#define MB 	(KB * KB)

void make_system_report(system_t* data)
{
    time_t current_time     = time(NULL);
    struct tm* current_date = localtime(&current_time);

    char report_name[MAX_REPORT_NAME_SIZE];
    sprintf(report_name, "../resources/MySysInfo Report [%02d-%02d-%04d %02d:%02d:%02d].txt",
            current_date->tm_mday, current_date->tm_mon + 1, current_date->tm_year + 1900,
            current_date->tm_hour, current_date->tm_min, current_date->tm_sec);

    FILE* file_ptr = NULL;

    if ((file_ptr = fopen(report_name, "w")) == NULL) 
    {
        perror("Error to open file in \"report.c\" : make_system_report()");
        return;
    }
    fprintf(file_ptr, "================== MySysInfo System Report ==================\n\n");
    fprintf(file_ptr, "Date & Time: [%02d-%02d-%04d %02d:%02d:%02d]\n\n",
            current_date->tm_mday, current_date->tm_mon + 1, current_date->tm_year + 1900,
            current_date->tm_hour, current_date->tm_min, current_date->tm_sec);

    // Сведения о системе:
    //     - Имя хоста: [имя хоста]
    //     - Операционная система: [операционная система]
    //     - Версия операционной системы: [версия операционной системы]
    //     - Архитектура процессора: [архитектура процессора]

    //refresh_cpu_clocks(data->cpu, selected_processor_id);
    fprintf(file_ptr, "CPU Information:\n");
    for (uint32_t i = 0; i < data->cpu->processors_num; i++)
    {
        fprintf(file_ptr, " - Processor ID: %d\n", i);
        fprintf(file_ptr, "   - Name: %s\n", data->cpu->compound[i].model_name);
        fprintf(file_ptr, "   - Cores: %u\n", data->cpu->compound[i].cores_num);
        fprintf(file_ptr, "   - Threads: %u\n", data->cpu->compound[i].threads_num);
        fprintf(file_ptr, "   - Model number: %u\n", data->cpu->compound[i].model_number);
        fprintf(file_ptr, "   - Family number: %u\n", data->cpu->compound[i].family_number);
        fprintf(file_ptr, "   - Stepping number: %u\n", data->cpu->compound[i].stepping_number);
        fprintf(file_ptr, "   - Cpuid level: %u\n", data->cpu->compound[i].cpuid_level);
        fprintf(file_ptr, "   - Clflush size: %u\n", data->cpu->compound[i].clflush_size);
        fprintf(file_ptr, "   - Cache allignment: %u\n", data->cpu->compound[i].cache_alignment);
        fprintf(file_ptr, "   - Physical number: %u\n", data->cpu->compound[i].phys_cpus_num);
        fprintf(file_ptr, "   - Microcode name: %s\n", data->cpu->compound[i].microcode_name);
        fprintf(file_ptr, "   - Byte order: %s\n",
				            data->cpu->compound[i].byte_oder == LITTLE_ENDIAN_ORDER ? "little endian" : "big endian");
        fprintf(file_ptr, "   - Bogomips: %0.2f\n", data->cpu->compound[i].bogomips);
        fprintf(file_ptr, "   - Core ID: %d\n", data->cpu->compound[i].topology.core_id);
        fprintf(file_ptr, "   - Frequency:\n");
        fprintf(file_ptr, "     - Max:        %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_max / MHZ);
        fprintf(file_ptr, "     - Current:    %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_cur / MHZ);
        fprintf(file_ptr, "     - Base:       %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_base / MHZ);
        fprintf(file_ptr, "     - Min:        %0.2fMHz\n", (double)data->cpu->compound[i].frequency.freq_min / MHZ);
        fprintf(file_ptr, "     - Scaling governor: %s\n", data->cpu->compound[i].frequency.freq_scaling_governor);
        fprintf(file_ptr, "     - Latency:    %d\n", data->cpu->compound[i].frequency.transition_latency);
        fprintf(file_ptr, "     - Affected processors: %d\n", data->cpu->compound[i].frequency.affected_cpus);
        fprintf(file_ptr, "   - Cache:\n");
        fprintf(file_ptr, "     - Level 1 (D) size:      %uKB\n", data->cpu->compound[i].cache.l1_data_size);
        fprintf(file_ptr, "     - Level 1 (I) size:      %uKB\n", data->cpu->compound[i].cache.l1_inst_size);
        fprintf(file_ptr, "     - Level 2 size:          %uKB\n", data->cpu->compound[i].cache.l2_size);
        fprintf(file_ptr, "     - Level 3 size:          %uKB\n\n", data->cpu->compound[i].cache.l3_size);
        fprintf(file_ptr, "     - Level 1 (D) line size: %uKB\n", data->cpu->compound[i].cache.l1_data_line_size);
        fprintf(file_ptr, "     - Level 1 (I) line size: %uKB\n", data->cpu->compound[i].cache.l1_inst_line_size);
        fprintf(file_ptr, "     - Level 2 line size:     %uKB\n", data->cpu->compound[i].cache.l2_line_size);
        fprintf(file_ptr, "     - Level 3 line size:     %uKB\n\n", data->cpu->compound[i].cache.l3_line_size);
        fprintf(file_ptr, "     - Level 1 (D) sets:      %u\n", data->cpu->compound[i].cache.l1_data_sets);
        fprintf(file_ptr, "     - Level 1 (I) sets:      %u\n", data->cpu->compound[i].cache.l1_inst_sets);
        fprintf(file_ptr, "     - Level 2 sets:          %u\n", data->cpu->compound[i].cache.l2_sets);
        fprintf(file_ptr, "     - Level 3 sets:          %u\n\n", data->cpu->compound[i].cache.l3_sets);
        fprintf(file_ptr, "     - Level 1 (D) ways:      %u\n", data->cpu->compound[i].cache.l1_data_ways);
        fprintf(file_ptr, "     - Level 1 (I) ways:      %u\n", data->cpu->compound[i].cache.l1_inst_ways);
        fprintf(file_ptr, "     - Level 2 ways:          %u\n", data->cpu->compound[i].cache.l2_ways);
        fprintf(file_ptr, "     - Level 3 ways:          %u\n", data->cpu->compound[i].cache.l3_ways);
        if (data->cpu->compound[i].cache.levels_num > 3)
	    {
		    fprintf(file_ptr, "     - Level 4 (I) size: %uKB\n", data->cpu->compound[i].cache.l4_size);
		    fprintf(file_ptr, "     - Level 4 (I) line size: %uKB\n", data->cpu->compound[i].cache.l4_line_size);
		    fprintf(file_ptr, "     - Level 4 (I) sets: %u\n", data->cpu->compound[i].cache.l4_sets);
		    fprintf(file_ptr, "     - Level 4 (I) ways: %u\n", data->cpu->compound[i].cache.l4_ways);
	    }
    }
    //calculate_total_cpu_load(data->cpu, graph_points_num);
    fprintf(file_ptr, "\n - Current CPU AVG Load: %0.1f%%\n\n", data->cpu->current_load.avg_load);
    //calculate_cpu_cores_load(data->cpu); 
    fprintf(file_ptr, " - Current Cores Load:\n");
    for (uint32_t i = 0; i < data->cpu->processors_num; i++)
        fprintf(file_ptr, "   - CORE#%d: %0.2f%%\n", i, data->cpu->current_load.cores_load[i].user 
                                                    + data->cpu->current_load.cores_load[i].wait 
                                                    + data->cpu->current_load.cores_load[i].sys);
    fprintf(file_ptr, "\nMemory Information:\n");
    fprintf(file_ptr, " - Pages:\n");
    fprintf(file_ptr, "   - Anon Pages:  %0.1fMB\n", data->memory->memory_usage.anon_pages / KB);
    fprintf(file_ptr, "   - Page Tables: %0.1fMB\n", data->memory->memory_usage.page_tables / KB);
    fprintf(file_ptr, " - Activity:\n");
    fprintf(file_ptr, "   - Active:   %0.1fMB\n", data->memory->memory_usage.active / KB);
    fprintf(file_ptr, "   - Inactive: %0.1fMB\n\n", data->memory->memory_usage.active / KB);
    fprintf(file_ptr, " - Shared: %0.1fMB\n", data->memory->memory_usage.shmem / KB);
    fprintf(file_ptr, " - Mapped: %0.1fMB\n\n", data->memory->memory_usage.mapped / KB);
    fprintf(file_ptr, " - RAM Total:  %0.1fMB\n", data->memory->memory_usage.total / KB);
    fprintf(file_ptr, " - Swap Total: %0.1fMB\n\n", data->memory->memory_usage.swap_total / KB);
    fprintf(file_ptr, " - RAM Usage:   %0.1fMB(%3.1lf%%)\n", data->memory->memory_usage.usage / KB, 
														data->memory->memory_percentage.usage);
    fprintf(file_ptr, " - RAM Buffers: %0.1fMB(%3.1lf%%)\n", data->memory->memory_usage.buffers / KB,
														data->memory->memory_percentage.buffers);                                                    
    fprintf(file_ptr, " - RAM Cached:  %0.1fMB(%3.1lf%%)\n", data->memory->memory_usage.cached / KB,
														 data->memory->memory_percentage.cached);
    fprintf(file_ptr, " - RAM Free:    %0.1fMB(%3.1lf%%)\n\n", data->memory->memory_usage.free / KB,
														 data->memory->memory_percentage.free);
    fprintf(file_ptr, " - Swap Usage:  %0.1fMB(%3.1lf%%)\n", data->memory->memory_usage.swap_usage / KB,
														 data->memory->memory_percentage.swap_usage);
    fprintf(file_ptr, " - Swap Free:   %0.1fMB(%3.1lf%%)\n\n", data->memory->memory_usage.swap_free / KB,
														 data->memory->memory_percentage.swap_free);

    fprintf(file_ptr, "Network Information:\n");
    for (uint32_t i = 0 ; i < data->network->interfaces_num; i++)
    {
        fprintf(file_ptr, " - Interface %s (%d/%d)\n", data->network->stat[i].interface_name, 
                                                        i + 1, 
                                                        data->network->interfaces_num);
        fprintf(file_ptr, "   - Received:\n");
        fprintf(file_ptr, "     - Current Bandwidth: %0.2f kBit/s\n", data->network->stat[i].r_bandwith.cur / KB);
        fprintf(file_ptr, "     - Avg Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].r_bandwith.avg / KB);
        fprintf(file_ptr, "     - Min Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].r_bandwith.min / KB);
        fprintf(file_ptr, "     - Max Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].r_bandwith.max / KB);
        fprintf(file_ptr, "     - Total Received:    %0.2f MByte\n", data->network->stat[i].r_bytes / MB);
        fprintf(file_ptr, "   - Transmitted:\n");
        fprintf(file_ptr, "     - Current Bandwidth: %0.2f kBit/s\n", data->network->stat[i].t_bandwith.cur / KB);
        fprintf(file_ptr, "     - Avg Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].t_bandwith.avg / KB);
        fprintf(file_ptr, "     - Min Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].t_bandwith.min / KB);
        fprintf(file_ptr, "     - Max Bandwidth:     %0.2f kBit/s\n", data->network->stat[i].t_bandwith.max / KB);
        fprintf(file_ptr, "     - Total Transmitted: %0.2f MByte\n", data->network->stat[i].t_bytes / MB);
        fprintf(file_ptr, "   - Received packets:    %lu\n", data->network->stat[i].r_packets);
        fprintf(file_ptr, "   - Received errors:     %lu\n", data->network->stat[i].r_errs);
        fprintf(file_ptr, "   - Received drop:       %lu\n", data->network->stat[i].r_drop);
        fprintf(file_ptr, "   - Transmitted packets: %lu\n", data->network->stat[i].t_packets);
        fprintf(file_ptr, "   - Transmitted errors:  %lu\n", data->network->stat[i].t_errs);
        fprintf(file_ptr, "   - Transmitted drop:    %lu\n", data->network->stat[i].t_drop);
    }

    fprintf(file_ptr, "\nPCI Devices Information:\n");
    for (uint32_t i = 0 ; i < data->pci->pci_dev_num; i++)
    {
        fprintf(file_ptr, " - Device (%d/%d)\n", i + 1, data->pci->pci_dev_num);
        fprintf(file_ptr, "   - Slot: %s\n", data->pci->devices[i].slot_name);
        fprintf(file_ptr, "   - Class: %s\n", data->pci->devices[i].class_name);
        fprintf(file_ptr, "   - Subclass: %s\n", 
                            data->pci->devices[i].subclass_name ? data->pci->devices[i].subclass_name : "Not Found");
        fprintf(file_ptr, "   - Interface: %s\n", 
                            data->pci->devices[i].interface_name ? data->pci->devices[i].interface_name : "Not Found");
        fprintf(file_ptr, "   - Vendor Name: %s\n", data->pci->devices[i].vendor_name);
        fprintf(file_ptr, "   - Vendor ID: %s\n", data->pci->devices[i].vendor_id);
        fprintf(file_ptr, "   - Device Name: %s\n",
                            data->pci->devices[i].device_name ? data->pci->devices[i].device_name : "Not Found");
        fprintf(file_ptr, "   - Device ID: %s\n", data->pci->devices[i].device_id);
        fprintf(file_ptr, "   - Modalias: %s\n", data->pci->devices[i].modalias);
    }

    fprintf(file_ptr, "\nSystem Sensors Statistics:\n");
    for (uint32_t i = 0 ; i < data->sensor->sensors_num; i++)
    {
        fprintf(file_ptr, " - Sensor (%d/%d)\n", i + 1, data->sensor->sensors_num);
        fprintf(file_ptr, "   - Sensor name: %s\n", data->sensor->sensors[i].name);
        fprintf(file_ptr, "   - Current temperature: %d\n", data->sensor->sensors[i].cur_temp);
        fprintf(file_ptr, "   - Min temperature: %d\n", data->sensor->sensors[i].min_temp);
        fprintf(file_ptr, "   - Max temperature: %d\n", data->sensor->sensors[i].max_temp);
    }                                                                               
                            
    fclose(file_ptr);
}

