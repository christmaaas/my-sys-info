#include "mem_utils.h"
#include "../utils/file_utils.h"
#include "../utils/string_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			memory->memory_usage.total = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "MemFree"))
		{
			memory->memory_usage.free = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "Buffers"))
		{
			memory->memory_usage.buffers = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "Cached"))
		{
			memory->memory_usage.cached = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "SwapTotal"))
		{
			memory->memory_usage.swap_total = atol(tokens[1]);
            count++;
		}
		else if(!strcmp(tokens[0], "SwapFree"))
		{
			memory->memory_usage.swap_free = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Active"))
		{
			memory->memory_usage.active = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Inactive"))
		{
			memory->memory_usage.inactive = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "AnonPages"))
		{
			memory->memory_usage.anon_pages = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Mapped"))
		{
			memory->memory_usage.mapped = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "Shmem"))
		{
			memory->memory_usage.shmem = atol(tokens[1]);
            count++;
		}
        else if(!strcmp(tokens[0], "PageTables"))
		{
			memory->memory_usage.page_tables = atol(tokens[1]);
            count++;
		}

        for (int i = 0; i < tokens_num; ++i)
            free(tokens[i]);

        free(tokens);
    }
    fclose(file_ptr);
}
