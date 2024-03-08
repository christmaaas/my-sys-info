#include "cpu_facility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cpu_init(cpu_t* cpu)
{
    FILE* file_ptr = NULL;
    char file_buffer[FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_CPUS_ONLINE_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_facility.c\" : get_num_of_processors()");
        return;
    }

    if (!fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr))
    {
        fclose(file_ptr);

        perror("Error to read file in \"cpu_facility.c\" : get_num_of_processors()");

        return;
    }

    fclose(file_ptr);

    char** readed_tokens = NULL;
    int tokens_num = 0;

    readed_tokens = strsplit(file_buffer, "-", &tokens_num); // "-" is a delim str for num of processors in "online" file

    cpu->processors_num = atoi(readed_tokens[1]) + 1; // number of processors is at index [1] in tokens and +1 cause of indexes

    cpu->compound = (cpucompound_t*)malloc(cpu->processors_num * sizeof(cpucompound_t));

    for (size_t i = 0; i < tokens_num; ++i)
        free(readed_tokens[i]);

    free(readed_tokens);
}

#define CPUINFO_FILE_BUFFER_SIZE 2048 // flags line can be longer than 1024, so 2048 is optimal
#define COUNT_OF_PROCESSOR_TOKENS 27

void scan_cpu_info(cpu_t* cpu)
{
    FILE* file_ptr = NULL;
    char file_buffer[CPUINFO_FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_CPUINFO_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_facility.c\" : mem_alloc_for_cores()");
        return;
    }

    char** file_tokens = NULL;
    char* all_tokens[COUNT_OF_PROCESSOR_TOKENS];
    int num_tokens = 0, tokens_count = 0, processor_id = 0;

    while (fgets(file_buffer, CPUINFO_FILE_BUFFER_SIZE, file_ptr))
    {
        if (file_buffer[0] == '\n') // info in "cpuinfo.txt" mapped by blocks separated by new line
        {
            tokens_count = 0;
            continue;
        }

        file_tokens = strsplit(file_buffer, "\t: ", &num_tokens);

        all_tokens[tokens_count++] = file_tokens[1];

        if (tokens_count == COUNT_OF_PROCESSOR_TOKENS)
        {
            for (size_t i = 0; i < COUNT_OF_PROCESSOR_TOKENS; ++i)
            {
                switch (i)
                {
                    case PROCESSOR_NUM:     { cpu->compound[processor_id].topology.thread_id = atoi(all_tokens[PROCESSOR_NUM]); break; }
                    case VENDOR_ID:         { cpu->compound[processor_id].vendor_name = all_tokens[VENDOR_ID];                  break; }
                    case CPU_FAMILY:        { cpu->compound[processor_id].family_number = atoi(all_tokens[CPU_FAMILY]);         break; }
                    case MODEL:             { cpu->compound[processor_id].model_number = atoi(all_tokens[MODEL]);               break; }
                    case MODEL_NAME:        { cpu->compound[processor_id].model_name = all_tokens[MODEL_NAME];                  break; }
                    case STEPPING:          { cpu->compound[processor_id].stepping_number = atoi(all_tokens[STEPPING]);         break; }
                    case MICROCODE:         { cpu->compound[processor_id].microcode_name = all_tokens[MICROCODE];               break; }
                    case PHYSICAL_ID:       { cpu->compound[processor_id].topology.socket_id = atoi(all_tokens[PHYSICAL_ID]);   break; }
                    case SIBLINGS:          { cpu->compound[processor_id].threads_num = atoi(all_tokens[SIBLINGS]);             break; }
                    case CORE_ID:           { cpu->compound[processor_id].topology.core_id = atoi(all_tokens[CORE_ID]);         break; }
                    case CPU_CORES:         { cpu->compound[processor_id].cores_num = atoi(all_tokens[CPU_CORES]);              break; }
                    case CPUID_LEVEL:       { cpu->compound[processor_id].cpuid_level = atoi(all_tokens[CPUID_LEVEL]);          break; }
                    case FLAGS:             { cpu->compound[processor_id].flags = all_tokens[FLAGS];                            break; }
                    case BUGS:              { cpu->compound[processor_id].bugs = all_tokens[BUGS];                              break; }
                    case BOGOMIPS:          { cpu->compound[processor_id].bogomips = atof(all_tokens[BOGOMIPS]);                break; }
                    case CLFLUSH_SIZE:      { cpu->compound[processor_id].clflush_size = atoi(all_tokens[CLFLUSH_SIZE]);        break; }
                    case CACHE_ALIGNMENT:   { cpu->compound[processor_id].cache_alignment = atoi(all_tokens[CACHE_ALIGNMENT]);  break; }
                    case ADDRESS_SIZES:     { cpu->compound[processor_id].address_sizes = all_tokens[ADDRESS_SIZES];            break; }
                    default:
                        break;
                }
            }
            processor_id++;
        }
    }
    fclose(file_ptr);

    // TODO
    // вызвать функция для получения архитектуры и т.д.
    // которых нет в cpuinfo
}

void scan_cpu_clocks(cpu_t* cpu)
{
    //TODO
}

void scan_cpu_topology(cpu_t* cpu)
{
    //TODO
}