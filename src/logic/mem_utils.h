#ifndef _MEM_UTILS_H
#define _MEM_UTILS_H

#include <stdint.h>

#define PATH_MEMINFO_FILE "/proc/meminfo"

typedef struct memory_load
{
	uint64_t usage;
	uint64_t total;
	uint64_t free;
	uint64_t buffers;
	uint64_t cached;
	uint64_t active;
	uint64_t inactive;

	uint64_t swap_usage;
    uint64_t swap_total;
	uint64_t swap_free;

	uint64_t anon_pages;
	uint64_t mapped;
	uint64_t shmem;
	uint64_t page_tables;
} memload_t;

typedef struct memory_percentage
{
	double usage;
	double free;
	double buffers;
	double cached;

	double swap_usage;
	double swap_free;
} mempercent_t;

typedef struct memory_info
{
    memload_t 	  memory_load;
	mempercent_t  memory_percentage;
} mem_t;

void scan_memory(mem_t* memory);

#endif /* _MEM_UTILS_H */