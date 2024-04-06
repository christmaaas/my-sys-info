#include "mem_utils.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

void scan_memory(mem_t* memory)
{
    FILE* file_ptr = NULL;
    char file_buffer[FILE_BUFFER_SIZE];

    if ((file_ptr = fopen(PATH_MEMINFO_FILE, "r")) == NULL)
    {   
        perror("Error to open file in \"mem_utils.c\" : scan_memory()");
        return;
    }

    int count = 0, tokens_num = 0;
    char** tokens = NULL;
    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr) && count < 12)
    {
        tokens = strsplit(file_buffer, ":", &tokens_num);

        if(!strcmp(tokens[0], "MemTotal"))
		{
			memory->memory_load.total = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "MemFree"))
		{
			memory->memory_load.free = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "Buffers"))
		{
			memory->memory_load.buffers = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "Cached"))
		{
			memory->memory_load.cached = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "SwapTotal"))
		{
			memory->memory_load.swap_total = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "SwapFree"))
		{
			memory->memory_load.swap_free = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Active"))
		{
			memory->memory_load.active = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Inactive"))
		{
			memory->memory_load.inactive = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "AnonPages"))
		{
			memory->memory_load.anon_pages = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Mapped"))
		{
			memory->memory_load.mapped = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Shmem"))
		{
			memory->memory_load.shmem = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "PageTables"))
		{
			memory->memory_load.page_tables = atol(tokens[1]);
            count++;
		}

        for (size_t i = 0; i < tokens_num; ++i)
            free(tokens[i]);

        free(tokens);
    }

    fclose(file_ptr);
}
