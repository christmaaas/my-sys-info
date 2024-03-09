#include <ncurses.h>
#include <cpuid.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <linux/sysinfo.h>

#include "sys.h"

#include "../facilities/cpu_facility.h"

int main() 
{
    system_t* system = (system_t*)malloc(sizeof(system_t));

    system->cpu = (cpu_t*)malloc(sizeof(cpu_t));

    cpu_init(system->cpu);

    scan_cpu_basic_info(system->cpu);

    cpucompound_t a = system->cpu->compound[0];

    int bnb = a.cache.l4_line_size;
    int bnb1 = a.cache.l4_sets_count;
    int bnb2 = a.cache.l4_size;
    int bnb3 = a.cache.l4_ways_of_associativity;

    free(a.vendor_name);
    free(a.model_name);
    free(a.microcode_name);
    free(a.flags);
    free(a.bugs);
    free(a.address_sizes);

    cpucompound_t a1 = system->cpu->compound[1];
    free(a1.vendor_name);
    free(a1.model_name);
    free(a1.microcode_name);
    free(a1.flags);
    free(a1.bugs);
    free(a1.address_sizes);
    cpucompound_t a2 = system->cpu->compound[2];
    free(a2.vendor_name);
    free(a2.model_name);
    free(a2.microcode_name);
    free(a2.flags);
    free(a2.bugs);
    free(a2.address_sizes);
    cpucompound_t a3 = system->cpu->compound[3];
    free(a3.vendor_name);
    free(a3.model_name);
    free(a3.microcode_name);
    free(a3.flags);
    free(a3.bugs);
    free(a3.address_sizes);
    cpucompound_t a4 = system->cpu->compound[4];
    free(a4.vendor_name);
    free(a4.model_name);
    free(a4.microcode_name);
    free(a4.flags);
    free(a4.bugs);
    free(a4.address_sizes);
    cpucompound_t a5 = system->cpu->compound[5];

    cpubyteorder_t peremenaya = a5.byte_oder;

    free(a5.vendor_name);
    free(a5.model_name);
    free(a5.microcode_name);
    free(a5.flags);
    free(a5.bugs);
    free(a5.address_sizes);
    cpucompound_t a6 = system->cpu->compound[6];
    free(a6.vendor_name);
    free(a6.model_name);
    free(a6.microcode_name);
    free(a6.flags);
    free(a6.bugs);
    free(a6.address_sizes);
    cpucompound_t a7 = system->cpu->compound[7];
    free(a7.vendor_name);
    free(a7.model_name);
    free(a7.microcode_name);
    free(a7.flags);
    free(a7.bugs);
    free(a7.address_sizes);
    cpucompound_t a8 = system->cpu->compound[8];
    free(a8.vendor_name);
    free(a8.model_name);
    free(a8.microcode_name);
    free(a8.flags);
    free(a8.bugs);
    free(a8.address_sizes);
    cpucompound_t a9 = system->cpu->compound[9];
    free(a9.vendor_name);
    free(a9.model_name);
    free(a9.microcode_name);
    free(a9.flags);
    free(a9.bugs);
    free(a9.address_sizes);
    cpucompound_t a10 = system->cpu->compound[10];
    free(a10.vendor_name);
    free(a10.model_name);
    free(a10.microcode_name);
    free(a10.flags);
    free(a10.bugs);
    free(a10.address_sizes);
    cpucompound_t a11 = system->cpu->compound[11];
    free(a11.vendor_name);
    free(a11.model_name);
    free(a11.microcode_name);
    free(a11.flags);
    free(a11.bugs);
    free(a11.address_sizes);
    cpucompound_t a12 = system->cpu->compound[12];
    free(a12.vendor_name);
    free(a12.model_name);
    free(a12.microcode_name);
    free(a12.flags);
    free(a12.bugs);
    free(a12.address_sizes);
    cpucompound_t a13 = system->cpu->compound[13];
    free(a13.vendor_name);
    free(a13.model_name);
    free(a13.microcode_name);
    free(a13.flags);
    free(a13.bugs);
    free(a13.address_sizes);
    cpucompound_t a14 = system->cpu->compound[14];
    free(a14.vendor_name);
    free(a14.model_name);
    free(a14.microcode_name);
    free(a14.flags);
    free(a14.bugs);
    free(a14.address_sizes);
    cpucompound_t a15 = system->cpu->compound[15];
    free(a15.vendor_name);
    free(a15.model_name);
    free(a15.microcode_name);
    free(a15.flags);
    free(a15.bugs);
    free(a15.address_sizes);

    return 0;
}
