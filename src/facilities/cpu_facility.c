#include "cpu_facility.h"

#include <stdio.h>

void get_num_of_processors(cpu_t* cpu_info)
{
    FILE* file_ptr = NULL;

    if((file_ptr = fopen(PATH_CPUS_ONLINE_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_facility.c\" : get_num_of_processors()");
        return;
    }

    // преобразовать строку "0-15" в число 15
    // или ф-ия или макросом



}

#define CPUINFO_FILE_BUFFER_SIZE 2048 // flags line can be longer than 1024, so 2048 is optimal

void afgdfgdfg(cpu_t* cpu_info)
{
    if(cpu_info->compound != NULL)
        return;

    char file_buffer[CPUINFO_FILE_BUFFER_SIZE];

    FILE* cpu_file_ptr = NULL;

    if((cpu_file_ptr = fopen(PATH_CPUINFO_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"cpu_facility.c\" : mem_alloc_for_cores()");
        return;
    }

    while(fgets(file_buffer, CPUINFO_FILE_BUFFER_SIZE, cpu_file_ptr))
    {
        
    }





}