#ifndef _MEM_UTILS_H
#define _MEM_UTILS_H

#include <stdint.h>

#define PATH_MEMINFO_FILE "/proc/meminfo"

#define MAX_MEM_LOAD_HISTORY_SIZE 200

typedef struct memory_usage
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
} memusage_t;

typedef struct memory_percentage
{
	double usage;
	double free;
	double buffers;
	double cached;
	double swap_usage;
	double swap_free;
} mempercent_t;

typedef struct mem_load
{
    double   ram_load_history[MAX_MEM_LOAD_HISTORY_SIZE];
	double   swap_load_history[MAX_MEM_LOAD_HISTORY_SIZE];
    uint32_t cur_point;
} memload_t;

typedef struct memory_info
{
    memusage_t 	 memory_usage;
	mempercent_t memory_percentage;
	memload_t	 current_load;
} mem_t;

void scan_memory(mem_t* memory);

#endif /* _MEM_UTILS_H */