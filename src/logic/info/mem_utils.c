#include "mem_utils.h"
#include "../../utils/file_utils.h"
#include "../../utils/string_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_TOKENS_COUNT 12

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
    while (fgets(file_buffer, FILE_BUFFER_SIZE, file_ptr) && count < MEMORY_TOKENS_COUNT)
    {
        tokens = strsplit(file_buffer, ":", &tokens_num);

        if (!strcmp(tokens[0], "MemTotal"))
		{
			memory->usage_stats.total = atol(tokens[1]);
            count++;
		}
		else if (!strcmp(tokens[0], "MemFree"))
		{
			memory->usage_stats.free = atol(tokens[1]);
            count++;
		}
		else if (!strcmp(tokens[0], "Buffers"))
		{
			memory->usage_stats.buffers = atol(tokens[1]);
            count++;
		}
		else if (!strcmp(tokens[0], "Cached"))
		{
			memory->usage_stats.cached = atol(tokens[1]);
            count++;
		}
		else if (!strcmp(tokens[0], "SwapTotal"))
		{
			memory->usage_stats.swap_total = atol(tokens[1]);
            count++;
		}
		else if (!strcmp(tokens[0], "SwapFree"))
		{
			memory->usage_stats.swap_free = atol(tokens[1]);
            count++;
		}
        else if (!strcmp(tokens[0], "Active"))
		{
			memory->usage_stats.active = atol(tokens[1]);
            count++;
		}
        else if (!strcmp(tokens[0], "Inactive"))
		{
			memory->usage_stats.inactive = atol(tokens[1]);
            count++;
		}
        else if (!strcmp(tokens[0], "AnonPages"))
		{
			memory->usage_stats.anon_pages = atol(tokens[1]);
            count++;
		}
        else if (!strcmp(tokens[0], "Mapped"))
		{
			memory->usage_stats.mapped = atol(tokens[1]);
            count++;
		} 
        else if (!strcmp(tokens[0], "Shmem"))
		{
			memory->usage_stats.shmem = atol(tokens[1]);
            count++;
		}
        else if (!strcmp(tokens[0], "PageTables"))
		{
			memory->usage_stats.page_tables = atol(tokens[1]);
            count++;
		}

        for (int i = 0; i < tokens_num; ++i)
            free(tokens[i]);
        free(tokens);
    }
	
    fclose(file_ptr);
}
