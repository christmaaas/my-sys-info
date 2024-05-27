#include "cpu_utils.h"
#include "../../utils/file_utils.h"
#include "../../utils/string_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_cpu_cores(cpu_t* cpu)
{
    FILE* file_ptr = NULL;
    char file_buffer[FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_CPUS_PRESENT_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_utils.c\" : init_cpu_cores()");
        return;
    }

    if (!fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr))
    {
        fclose(file_ptr);
        perror("Error to read file in \"cpu_utils.c\" : init_cpu_cores()");
        return;
    }

    fclose(file_ptr);

    char** readed_tokens = NULL;
    int tokens_num = 0;

    // "-" is a delim str for num of processors in "online" file
    readed_tokens = strsplit(file_buffer, "-", &tokens_num);

    /* number of processors is at index [1] in tokens
       and +1 cause of indexes  */
    cpu->processors_num = atoi(readed_tokens[1]) + 1;   

    cpu->compound                = (cpucompound_t*)calloc(cpu->processors_num, sizeof(cpucompound_t));
    cpu->current_load.cores      = (loadtype_t*)calloc(cpu->processors_num, sizeof(loadtype_t));
    cpu->current_load.cores_load = (loadpercent_t*)calloc(cpu->processors_num, sizeof(loadpercent_t));

    for (int i = 0; i < tokens_num; ++i)
        free(readed_tokens[i]);
    free(readed_tokens);
}

#define CPU_FILE_BUFFER_SIZE 2048 // flags line can be longer than 1024, so 2048 is optimal
#define COUNT_OF_PROCESSOR_TOKENS 27

typedef enum cpu_info_tokens
{
    PROCESSOR_NUM   = 0,
    VENDOR_ID       = 1,
    CPU_FAMILY      = 2,
    MODEL           = 3,
    MODEL_NAME      = 4,
    STEPPING        = 5,
    MICROCODE       = 6,
    FREQUENCY_MHZ   = 7,
    CACHE_SIZE      = 8,
    PHYSICAL_ID     = 9,
    SIBLINGS        = 10,
    CORE_ID         = 11,
    CPU_CORES       = 12,
    APICID          = 13,
    INITIAL_APICID  = 14,
    FPU             = 15,
    FPU_EXCEPTION   = 16,
    CPUID_LEVEL     = 17,
    WP              = 18,
    FLAGS           = 19,
    VMX_FLAGS       = 20,
    BUGS            = 21,
    BOGOMIPS        = 22,
    CLFLUSH_SIZE    = 23,
    CACHE_ALIGNMENT = 24,
    ADDRESS_SIZES   = 25,
    POWER_MANAGMENT = 26
} cpu_info_tokens_t;

void scan_cpu_basic_info(cpu_t* cpu)
{
    FILE* file_ptr = NULL;
    char file_buffer[CPU_FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_CPUINFO_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_utils.c\" : scan_cpu_basic_info()");
        return;
    }

    char** file_tokens = NULL;
    char* all_tokens[COUNT_OF_PROCESSOR_TOKENS];
    int num_tokens = 0, tokens_count = 0, processor_id = 0;

    while (fgets(file_buffer, CPU_FILE_BUFFER_SIZE, file_ptr))
    {
        // info in "cpuinfo.txt" mapped by blocks separated by new line
        if (file_buffer[0] == '\n') 
        {
            tokens_count = 0;
            continue;
        }

        file_tokens = strsplit(file_buffer, ": ", &num_tokens);

        if(num_tokens != 1)
            CUT_STRING_BY_LENGTH(file_tokens[1]);

        all_tokens[tokens_count++] = file_tokens[1];

        if (tokens_count == COUNT_OF_PROCESSOR_TOKENS)
        {
            for (size_t i = 0; i < COUNT_OF_PROCESSOR_TOKENS; ++i)
            {
                switch (i)
                {
                    case PROCESSOR_NUM:     
                    { 
                        cpu->compound[processor_id].topology.thread_id = atoi(all_tokens[PROCESSOR_NUM]); 
                        free(all_tokens[PROCESSOR_NUM]);
                        break; 
                    }
                    case VENDOR_ID:         
                    { 
                        cpu->compound[processor_id].vendor_name = all_tokens[VENDOR_ID];                  
                        break; 
                    }
                    case CPU_FAMILY:        
                    { 
                        cpu->compound[processor_id].family_number = atoi(all_tokens[CPU_FAMILY]);
                        free(all_tokens[CPU_FAMILY]);         
                        break; 
                    }
                    case MODEL:             
                    { 
                        cpu->compound[processor_id].model_number = atoi(all_tokens[MODEL]); 
                        free(all_tokens[MODEL]);              
                        break; 
                    }
                    case MODEL_NAME:        
                    { 
                        cpu->compound[processor_id].model_name = all_tokens[MODEL_NAME];                  
                        break; 
                    }
                    case STEPPING:          
                    { 
                        cpu->compound[processor_id].stepping_number = atoi(all_tokens[STEPPING]);   
                        free(all_tokens[STEPPING]);      
                        break; 
                    }
                    case MICROCODE:         
                    { 
                        cpu->compound[processor_id].microcode_name = all_tokens[MICROCODE];               
                        break; 
                    }
                    case PHYSICAL_ID:       
                    { 
                        cpu->compound[processor_id].topology.socket_id = atoi(all_tokens[PHYSICAL_ID]);
                        free(all_tokens[PHYSICAL_ID]);
                        break; 
                    }
                    case SIBLINGS:          
                    { 
                        cpu->compound[processor_id].threads_num = atoi(all_tokens[SIBLINGS]);
                        free(all_tokens[SIBLINGS]);             
                        break; 
                    }
                    case CORE_ID:           
                    { 
                        cpu->compound[processor_id].topology.core_id = atoi(all_tokens[CORE_ID]);
                        free(all_tokens[CORE_ID]);           
                        break; 
                    }
                    case CPU_CORES:         
                    { 
                        cpu->compound[processor_id].cores_num = atoi(all_tokens[CPU_CORES]);  
                        free(all_tokens[CPU_CORES]);              
                        break; 
                    }
                    case CPUID_LEVEL:       
                    { 
                        cpu->compound[processor_id].cpuid_level = atoi(all_tokens[CPUID_LEVEL]);
                        free(all_tokens[CPUID_LEVEL]);          
                        break; 
                    }
                    case BOGOMIPS:          
                    { 
                        cpu->compound[processor_id].bogomips = atoi(all_tokens[BOGOMIPS]);
                        free(all_tokens[BOGOMIPS]);                   
                        break; 
                    }
                    case CACHE_ALIGNMENT:   
                    { 
                        cpu->compound[processor_id].cache_alignment = atoi(all_tokens[CACHE_ALIGNMENT]);
                        free(all_tokens[CACHE_ALIGNMENT]);   
                        break; 
                    }
                    default:
                        break;
                }
            }

            char* byte_order_str = get_file(PATH_CPU_BYTE_ORDER_FILE);

            if (!strcmp(byte_order_str, "little"))
                cpu->compound[processor_id].byte_oder = LITTLE_ENDIAN_ORDER;
            else
                cpu->compound[processor_id].byte_oder = BIG_ENDIAN_ORDER;

            processor_id++;

            free(all_tokens[FREQUENCY_MHZ]);
            free(all_tokens[CACHE_SIZE]);
            free(all_tokens[APICID]);
            free(all_tokens[INITIAL_APICID]);
            free(all_tokens[FPU]);
            free(all_tokens[FPU_EXCEPTION]);
            free(all_tokens[WP]);
            free(all_tokens[FLAGS]);
            free(all_tokens[VMX_FLAGS]);
            free(all_tokens[BUGS]);
            free(all_tokens[CLFLUSH_SIZE]);
            free(all_tokens[ADDRESS_SIZES]);
            free(byte_order_str);
        }
    }
    fclose(file_ptr);
}

typedef enum cpu_cache_levels
{
    L1_DATA_LEVEL        = 0,
    L1_INSTRUCTION_LEVEL = 1,
    L2_LEVEL             = 2,
    L3_LEVEL             = 3,
    L4_LEVEL             = 4
} cache_level_t;

void scan_cpu_cache(cpu_t* cpu)
{
    char cache_path[MAX_FILE_PATH_LEN];
    char cache_index_path[MAX_FILE_PATH_LEN];

    char *size_path = NULL, *line_size_path = NULL, *sets_count = NULL, *ways_of_associativity_path = NULL;
    for (uint32_t cpu_id = 0; cpu_id < cpu->processors_num; ++cpu_id)
    {
        snprintf(cache_path, MAX_FILE_PATH_LEN, "/sys/devices/system/cpu/cpu%u/cache", cpu_id);

        int count_of_cache_files = get_count_of_files_name(cache_path, "index");

        // -1 cause of l1 cache has 2 files except one
        cpu->compound[cpu_id].cache.levels_num = count_of_cache_files - 1;

        for (int level = 0; level < count_of_cache_files; ++level)
        {
            snprintf(cache_index_path, MAX_FILE_PATH_LEN, "/sys/devices/system/cpu/cpu%u/cache/index%d", cpu_id, level);

            size_path                  = strconcat(cache_index_path, "/size");
            line_size_path             = strconcat(cache_index_path, "/coherency_line_size");
            sets_count                 = strconcat(cache_index_path, "/number_of_sets");
            ways_of_associativity_path = strconcat(cache_index_path, "/ways_of_associativity");

            switch (level)
            {
                case L1_DATA_LEVEL: 
                {
                    cpu->compound[cpu_id].cache.l1_data_size      = get_file_int(size_path);
                    cpu->compound[cpu_id].cache.l1_data_line_size = get_file_int(line_size_path);
                    cpu->compound[cpu_id].cache.l1_data_sets      = get_file_int(sets_count);
                    cpu->compound[cpu_id].cache.l1_data_ways      = get_file_int(ways_of_associativity_path);

                    break;
                }
                case L1_INSTRUCTION_LEVEL: 
                {
                    cpu->compound[cpu_id].cache.l1_inst_size      = get_file_int(size_path);
                    cpu->compound[cpu_id].cache.l1_inst_line_size = get_file_int(line_size_path);
                    cpu->compound[cpu_id].cache.l1_inst_sets      = get_file_int(sets_count);
                    cpu->compound[cpu_id].cache.l1_inst_ways      = get_file_int(ways_of_associativity_path);

                    break;
                }
                case L2_LEVEL: 
                {
                    cpu->compound[cpu_id].cache.l2_size      = get_file_int(size_path);
                    cpu->compound[cpu_id].cache.l2_line_size = get_file_int(line_size_path);
                    cpu->compound[cpu_id].cache.l2_sets      = get_file_int(sets_count);
                    cpu->compound[cpu_id].cache.l2_ways      = get_file_int(ways_of_associativity_path);

                    break;
                }
                case L3_LEVEL: 
                {
                    cpu->compound[cpu_id].cache.l3_size      = get_file_int(size_path);
                    cpu->compound[cpu_id].cache.l3_line_size = get_file_int(line_size_path);
                    cpu->compound[cpu_id].cache.l3_sets      = get_file_int(sets_count);
                    cpu->compound[cpu_id].cache.l3_ways      = get_file_int(ways_of_associativity_path);

                    break;
                }
                case L4_LEVEL: 
                {
                    cpu->compound[cpu_id].cache.l4_size      = get_file_int(size_path);
                    cpu->compound[cpu_id].cache.l4_line_size = get_file_int(line_size_path);
                    cpu->compound[cpu_id].cache.l4_sets      = get_file_int(sets_count);
                    cpu->compound[cpu_id].cache.l4_ways      = get_file_int(ways_of_associativity_path);

                    break;
                }
                default:
                    break;
            }
            free(size_path);
            free(line_size_path);
            free(sets_count);
            free(ways_of_associativity_path);
        }
    }
}

void scan_cpu_clocks(cpu_t* cpu)
{
    int count_of_freq_files = get_count_of_files_name(PATH_CPUFREQ_FILE, "policy");

    char policy_path[MAX_FILE_PATH_LEN];
    char* policy_content_path = NULL;
    for(int cpu_id = 0; cpu_id < count_of_freq_files; ++cpu_id)
    {
        snprintf(policy_path, MAX_FILE_PATH_LEN, "/sys/devices/system/cpu/cpufreq/policy%d", cpu_id);

        policy_content_path = strconcat(policy_path, "/base_frequency");
        cpu->compound[cpu_id].frequency.freq_base = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/scaling_max_freq");
        cpu->compound[cpu_id].frequency.freq_max = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/scaling_min_freq");
        cpu->compound[cpu_id].frequency.freq_min = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/scaling_cur_freq");
        cpu->compound[cpu_id].frequency.freq_cur = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/cpuinfo_transition_latency");
        cpu->compound[cpu_id].frequency.transition_latency = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/affected_cpus");
        cpu->compound[cpu_id].frequency.affected_cpus = get_file_int(policy_content_path);
        free(policy_content_path);

        policy_content_path = strconcat(policy_path, "/scaling_governor");
        cpu->compound[cpu_id].frequency.freq_scaling_governor = get_file(policy_content_path);
        free(policy_content_path);
    }
}

void refresh_cpu_clocks(cpu_t* cpu, const int proc_id)
{
    char policy_path[MAX_FILE_PATH_LEN];
    snprintf(policy_path, MAX_FILE_PATH_LEN, "/sys/devices/system/cpu/cpufreq/policy%d", proc_id);

    char* policy_content_path = strconcat(policy_path, "/scaling_cur_freq");
    cpu->compound[proc_id].frequency.freq_cur = get_file_int(policy_content_path);
    free(policy_content_path);
}

/* /proc/stat explanation:
   All of the numbers reported in this file are aggregates since the system booted.
   These numbers identify the amount of time the CPU has spent performing different kinds of work. 
   Time units are in USER_HZ or Jiffies (typically hundredths of a second).
   The first "cpu" line is an aggregate of all following "cpuN" lines
   The "cpu" lines description: */
/* Column	Name	Description	Kernel
    1	    user	 Time spent with normal processing in user mode.
    2	    nice	 Time spent with niced processes in user mode.
    3	    system	 Time spent running in kernel mode.
    4	    idle	 Time spent in vacations twiddling thumbs.
    5	    iowait	 Time spent waiting for I/O to completed. 
    ...     ...      ... */
 /* There may be more columns, depends on the kernel version
    For fairly accurate calcs, the given 5 are enough */

void scan_cpu_load_stat(cpu_t* cpu)
{
    FILE* file_ptr = NULL;
    char file_buffer[CPU_FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_STAT_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_utils.c\" : scan_cpu_load_stat()");
        return;
    }

    uint64_t user = 0, nice = 0, sys = 0, idle = 0, wait = 0;

    fgets(file_buffer, CPU_FILE_BUFFER_SIZE, file_ptr);

    if (strncmp(file_buffer, "cpu", 3))
		return;
        
    sscanf(file_buffer + 5, "%lu %lu %lu %lu %lu", 
                                            &user,
                                            &nice,
                                            &sys,
                                            &idle,
                                            &wait);

    // niced processes are also in user mode so we can add it to user processes	
	cpu->current_load.total.user = user + nice;
	cpu->current_load.total.sys  = sys;
	cpu->current_load.total.idle = idle;
    cpu->current_load.total.nice = nice;
    cpu->current_load.total.wait = wait;

    uint32_t core = 0;
    while (fgets(file_buffer, CPU_FILE_BUFFER_SIZE, file_ptr) && core != cpu->processors_num)
    {
        if (strncmp(file_buffer, "cpu", 3))
			break;
		
        sscanf(file_buffer + 5, "%lu %lu %lu %lu %lu", 
		                                        &user,
		                                        &nice,
		                                        &sys,
		                                        &idle,
                                                &wait);

        // niced processes are also in user mode so we can add it to user processes
        cpu->current_load.cores[core].user = user + nice;
        cpu->current_load.cores[core].sys  = sys;
	    cpu->current_load.cores[core].idle = idle;
        cpu->current_load.cores[core].nice = nice;
        cpu->current_load.cores[core].wait = wait;

        core++;
    }
    fclose(file_ptr);
}