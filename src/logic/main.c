#include <cpuid.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <linux/sysinfo.h>

#include "sys.h"
#include "../facilities/cpu_facility.h"
#include "../ui/main_ui.h"

int main() 
{
    // system_t* system = (system_t*)malloc(sizeof(system_t));

    // get_cpu_info(&(system->cpu));

    // cpucompound_t a1 = system->cpu->compound[1];

    // cpucompound_t a2 = system->cpu->compound[2];

    // cpucompound_t a3 = system->cpu->compound[3];

    // cpucompound_t a4 = system->cpu->compound[4];


    // cpucompound_t a5 = system->cpu->compound[5];

    // cpubyteorder_t peremenaya = a5.byte_oder;


    // cpucompound_t a6 = system->cpu->compound[6];

    // cpucompound_t a7 = system->cpu->compound[7];

    // cpucompound_t a8 = system->cpu->compound[8];

    // cpucompound_t a9 = system->cpu->compound[9];

    // cpucompound_t a10 = system->cpu->compound[10];

    // cpucompound_t a11 = system->cpu->compound[11];

    // cpucompound_t a12 = system->cpu->compound[12];

    // cpucompound_t a13 = system->cpu->compound[13];

    // cpucompound_t a14 = system->cpu->compound[14];

    // cpucompound_t a15 = system->cpu->compound[15];

    // free_cpu(system->cpu);

    main_window();

    return 0;
}
